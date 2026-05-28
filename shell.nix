{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    buildInputs = with pkgs; [
        gcc
        meson
        cmake
        pkg-config
        ninja
        glfw3
        libGL
        glm
    ];
}
