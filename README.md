# 我的个人博客

基于 [Hugo](https://gohugo.io/) + [Nix](https://nixos.org/) 搭建的个人博客，部署在 GitHub Pages 上。

## 特性

- ✅ **可复现的开发环境** — 用 Nix Flake 管理，`nix develop` 一键进入
- ✅ **本地预览** — `hugo server` 实时热重载
- ✅ **自动部署** — push 到 master 自动构建并发布到 GitHub Pages
- ✅ **Markdown 写作** — 专注内容，简单高效

## 前置条件

安装 [Nix](https://nixos.org/download/) 包管理器：

```bash
# Linux / macOS
curl -L https://nixos.org/nix/install | sh
```

> Windows 用户推荐使用 WSL2，然后在 WSL 中安装 Nix。

## 快速开始

### 1. 进入开发环境

```bash
nix develop
```

第一次运行会下载 Hugo 等依赖，之后进入一个包含完整开发工具的 shell。

### 2. 启动本地预览

```bash
hugo server
```

打开浏览器访问 <http://localhost:1313> 即可预览博客。修改内容会自动刷新。

### 3. 新建文章

```bash
# 新建一篇博客文章
hugo new posts/我的第一篇文章.md
```

文章会生成在 `content/posts/` 目录下，用你喜欢的编辑器打开编写即可。

> 新文章默认是草稿状态（`draft: true`），发布前记得改为 `draft: false`。

### 4. 构建静态站点

```bash
hugo
```

生成的静态文件会放在 `public/` 目录。

## 部署到 GitHub Pages

### 步骤 1：创建 GitHub 仓库

在 GitHub 上创建一个仓库（比如 `my-blog`），将代码推送到 `master` 分支。

### 步骤 2：启用 GitHub Pages

1. 进入仓库的 **Settings → Pages**
2. 在 **Build and deployment** 部分，将 **Source** 设置为 **GitHub Actions**

### 步骤 3：修改配置

编辑 `hugo.toml`，将 `baseURL` 改为你的实际地址：

```toml
# 如果是用户/组织站点（yourname.github.io）
baseURL = 'https://yourname.github.io/'

# 如果是项目站点
baseURL = 'https://yourname.github.io/my-blog/'
```

同时修改 `title`、`author` 等信息为你自己的。

### 步骤 4：推送代码

```bash
git add .
git commit -m "init: 初始化博客"
git push origin master
```

GitHub Actions 会自动构建并部署。完成后在仓库的 **Actions** 页面可以看到部署状态。

## 目录结构

```
.
├── flake.nix              # Nix Flake 配置（定义开发环境和构建）
├── flake.lock             # Nix 依赖锁定文件（自动生成）
├── hugo.toml              # Hugo 站点配置
├── content/               # 博客内容
│   ├── about.md           # 关于页面
│   └── posts/             # 博客文章
│       └── hello-world.md
├── themes/                # 主题（默认自带 minimal 简洁主题）
│   └── minimal/           # 内置极简主题
├── static/                # 静态资源（图片等）
├── public/                # 构建输出（git 忽略）
└── .github/
    └── workflows/
        └── deploy.yml     # GitHub Actions 部署配置
```

## 更换主题（可选）

项目自带了一个简洁的 `minimal` 主题，开箱即用。如果你想换成其他热门主题，比如 [PaperMod](https://github.com/adityatelange/hugo-PaperMod)：

```bash
# 添加主题为 git submodule
git submodule add https://github.com/adityatelange/hugo-PaperMod.git themes/PaperMod

# 修改 hugo.toml 中的 theme 配置
theme = 'PaperMod'
```

更多主题可以在 [Hugo Themes](https://themes.gohugo.io/) 网站上找到。

## 常用命令速查

| 命令 | 说明 |
|------|------|
| `nix develop` | 进入开发环境 |
| `hugo server` | 启动本地预览服务器 |
| `hugo server -D` | 预览时包含草稿 |
| `hugo new posts/xxx.md` | 新建文章 |
| `hugo new --kind post posts/xxx.md` | 使用模板新建文章 |
| `hugo` | 构建静态站点 |
| `hugo --minify` | 构建并压缩 |
| `nix build` | 使用 Nix 构建站点 |
| `nix flake update` | 更新 Nix 依赖（升级 Hugo 等） |

## 写作小贴士

### Front Matter

每篇 Markdown 文章顶部需要有 YAML front matter：

```yaml
---
title: "文章标题"
date: 2026-10-11T00:00:00+08:00
draft: false              # true = 草稿，不会发布
tags: ["标签1", "标签2"]
categories: ["分类"]
summary: "文章摘要"
---
```

### 插入图片

把图片放到 `static/images/` 目录，然后在文章中引用：

```markdown
![图片描述](/images/photo.jpg)
```

## 常见问题

### Q: `nix develop` 很慢怎么办？

第一次运行需要下载依赖，属于正常现象。后续会使用缓存，速度很快。

### Q: 如何升级 Hugo 版本？

```bash
nix flake update
```

这会更新 `flake.lock` 中的所有依赖到最新版本。

### Q: 可以不用 Nix，直接用 Hugo 吗？

当然可以。你也可以直接安装 Hugo 然后使用所有 `hugo` 命令。Nix 只是提供了一种可复现的环境管理方式。

### Q: 如何自定义域名？

1. 在仓库根目录的 `static/` 下创建 `CNAME` 文件，写入你的域名（如 `blog.example.com`）
2. 在你的 DNS 服务商添加 CNAME 记录，指向 `yourname.github.io`

## License

MIT
