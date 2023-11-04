{
  description = "infiniteBalls";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        cc = pkgs.gcc12;

        deps = with pkgs; [
          glibc
          gnumake
          csfml
        ] ++ [ cc ];

        mkCApp = name: pkgs.stdenv.mkDerivation rec {
          inherit name;
          src = ./.;

          makeFlags = [ "CC=${cc}/bin/gcc" ];
          buildInputs = deps;

          hardeningDisable = [ "format" "fortify" ];
          enableParallelBuilding = true;

          buildPhase = ''
            make ${name} NO_COV=1
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp ${name} $out/bin
          '';
        };

      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gcovr
            ltrace
            valgrind
            python311Packages.compiledb
            man-pages
            man-pages-posix
          ] ++ deps;
        };

        formatter = pkgs.nixpkgs-fmt;
        packages = {
          default = mkCApp "infiniteBalls";
        };
      });
}
