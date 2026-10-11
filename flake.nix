{
  description = "My personal blog built with Hugo";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        hugo = pkgs.hugo;
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            hugo
            pkgs.git
          ];
          shellHook = ''
            echo "=== Hugo 博客开发环境 ==="
            echo "Hugo 版本: $(hugo version)"
            echo ""
            echo "常用命令:"
            echo "  hugo server     - 启动本地预览服务器"
            echo "  hugo new posts/xxx.md  - 新建文章"
            echo "  hugo            - 构建静态站点到 public/"
            echo ""
          '';
        };

        packages.default = pkgs.stdenvNoCC.mkDerivation {
          name = "my-blog";
          src = self;
          buildInputs = [ hugo ];
          buildPhase = ''
            hugo --minify --baseURL "$BASE_URL" -d $out
          '';
          installPhase = ":";
        };

        apps.hugo = {
          type = "app";
          program = "${hugo}/bin/hugo";
        };
      }
    );
}
