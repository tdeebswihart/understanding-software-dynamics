{
  description =
    "Development tools for the projects in Understanding System Dynamics";

  inputs = { flake-utils.url = "github:numtide/flake-utils"; };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            cmake
            gcc
            (writeShellScriptBin "rebuild" ''
              set -euo pipefail

              GIT_DIR=$(git rev-parse --git-dir)
              if [ `basename $GIT_DIR` = ".git" ]; then
                  # handle normal git repos (with a .git dir)
                  pushd $GIT_DIR/..
              else
                # handle bare git repos (the repo IS a xxx.git dir)
                pushd $GIT_DIR
              fi
              trap "popd > /dev/null" EXIT

              mkdir -p build/$(uname -m)
              cd build/$(uname -m)
              ${cmake}/bin/cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchains/$(uname -m).cmake ../..
              make
            '')
          ];
        };
      });
}
