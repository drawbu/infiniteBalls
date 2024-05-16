{
  description = "infiniteBalls";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, ...} @ inputs:
    inputs.utils.lib.eachDefaultSystem (system: let
      pkgs = import inputs.nixpkgs {inherit system;};
    in {
      formatter = pkgs.alejandra;
      devShells.default = pkgs.mkShell {
        inputsFrom = builtins.attrValues self.packages.${system};
        env.MAKEFLAGS = "-j$(nproc)";
        packages = with pkgs; [
          valgrind
          man-pages
          man-pages-posix
        ];
      };
      packages = {
        default = pkgs.stdenv.mkDerivation {
          name = "infiniteBalls";
          src = ./.;

          makeFlags = [ "PREFIX=${placeholder "out"}/bin" ];
          nativeBuildInputs = with pkgs; [pkg-config];
          buildInputs = with pkgs; [csfml];
          enableParallelBuilding = true;
        };
        infiniteBalls = self.packages.${system}.default;
      };
    });
}
