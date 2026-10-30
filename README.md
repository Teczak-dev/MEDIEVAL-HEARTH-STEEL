# MEDIEVAL HEARTH & STEEL

![Status](https://img.shields.io/badge/status-prototype-orange)
![C%2B%2B](https://img.shields.io/badge/C%2B%2B-20-blue)
![Raylib](https://img.shields.io/badge/raylib-powered-black)
![License](https://img.shields.io/badge/license-non--commercial-red)

**MEDIEVAL HEARTH & STEEL** is a 2D game prototype (Remake of [RPG CPP](https://github.com/Teczak-dev/RPG-CPP)) built in C++20 using the
[raylib](https://www.raylib.com/) library. The project is in an early stage of
development and serves as a foundation for building a medieval world, characters,
and gameplay systems.

## Key information

- target platforms: macOS and Windows;
- technologies: C++20, raylib, Premake;
- separate input, interface, character, and map systems;
- game resources are located in the `resources/` directory;
- the project is not yet a finished, full game.
- map and chunk format: [`docs/map-format.md`](docs/map-format.md).
- implementation backlog: [`TODO.md`](TODO.md).

## Requirements

### macOS

- Xcode Command Line Tools (`clang`, `make`);
- macOS with OpenGL 3.3 support;
- Premake — the `build/premake5.osx` script downloads raylib during configuration.

### Windows

- Visual Studio 2022 or newer **or** MinGW-w64;
- `make` available in the MinGW environment if you use GNU compilation;
- Premake — the `build/premake5.exe` script downloads raylib during configuration.

## Building on macOS

```sh
cd build
./premake5.osx gmake
cd ..
make config=release_x64
```

You will find the built program in `bin/Release/`. On Apple Silicon Macs, you
can use the `release_arm64` configuration.

## Building on Windows

### Visual Studio

Run `build-VisualStudio2022.bat`, then open the generated Visual Studio
solution. Select the `Release` configuration and the `x64` platform.

### MinGW-w64

Run `build-MinGW-W64.bat`, then run the following command in the MinGW terminal:

```sh
make config=release_x64
```

You will find the built program in `bin/Release/`.

## Project structure

```text
src/          C++ source code and Windows resource files
resources/    graphics and other game resources
build/        Premake configuration and downloaded raylib library sources
bin/          local build output (ignored by Git)
```

After changing the Premake configuration, regenerate the project files. The
`build/external/` directory is created automatically and should not be committed.

## GitHub Actions — macOS and Windows builds

Adding automated builds is **moderately easy**: the configuration itself should
take several hours to one day if the goal is only compilation and downloadable
artifacts. GitHub Actions provides ready-to-use environments
`macos-latest` and `windows-latest`, so a workflow can:

1. check out the repository;
2. install or prepare Premake and the compiler;
3. generate the project;
4. build the `Release` version;
5. package `bin/Release/` as an artifact or attach it to a GitHub Release.

The main areas requiring attention are the differences between the MSVC/MinGW
compilers and Clang on macOS, downloading raylib during the build, and packaging
resources alongside the program. It is also worth deciding separately whether
the macOS build should target only Apple Silicon or Intel as well, and whether
the application should be signed and notarized. Without signing, the build will
work, but macOS may display Gatekeeper warnings.

## License

The code and original project materials are available under the non-commercial
license described in the [LICENSE](LICENSE) file. You may copy, modify, and
share them free of charge, but you may not sell them or use them commercially
without the author's written permission. When sharing them, always credit the
author:
**Mikołaj Sobczak**.

The raylib library and other external materials retain their own licenses.
