#define _POSIX_C_SOURCE 200809L
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

enum { N = 1024, REPEAT = 100000, ROUNDS = 11 };
static uint64_t data[N];
static volatile uint64_t sink;

__attribute__((noinline))
uint64_t serial(const uint64_t *a, int repeats) {
    uint64_t s = 0;
    for (int r = 0; r < repeats; ++r)
        for (int i = 0; i < N; ++i) s += a[i];
    return s;
}

__attribute__((noinline))
uint64_t parallel(const uint64_t *a, int repeats) {
    uint64_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
    for (int r = 0; r < repeats; ++r)
        for (int i = 0; i < N; i += 4) {
            s0 += a[i]; s1 += a[i + 1];
            s2 += a[i + 2]; s3 += a[i + 3];
        }
    return s0 + s1 + s2 + s3;
}

static double now(void) {
    struct timespec t;
    if (clock_gettime(CLOCK_MONOTONIC, &t) != 0) {
        perror("clock_gettime"); return -1;
    }
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main(void) {
    for (int i = 0; i < N; ++i) data[i] = (uint64_t)i + 1;
    /* Volatile pointer prevents reuse of a previous call's result. */
    uint64_t (* volatile fn[2])(const uint64_t *, int) = {serial, parallel};
    const char *names[2] = {"serial", "four"};
    for (int k = 0; k < 2; ++k) sink = fn[k](data, 1000);
    puts("round,variant,ms,result");
    for (int r = 0; r < ROUNDS; ++r) {
        for (int j = 0; j < 2; ++j) {
            int k = (r + j) % 2; /* Alternate measurement order. */
            double start = now();
            uint64_t value = fn[k](data, REPEAT);
            double end = now();
            sink = value;
            if (start < 0 || end < 0 || value != UINT64_C(52480000000))
                return 1;
            printf("%d,%s,%.6f,%" PRIu64 "\n",
                   r + 1, names[k], (end - start) * 1000, value);
        }
    }
    return 0;
}
