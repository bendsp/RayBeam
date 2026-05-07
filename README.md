# RayBeam

An open-source configurable C++ Raytracer

# Authors

- Benjamin Desprets [@bendsp](https://github.com/bendsp)
- Felix Stavonhagen [@Felixsta123](https://github.com/Felixsta123)
- Kentin Paille [@KentinPaille](https://github.com/KentinPaille)
- Paul Thiebault [@PaulThblt](https://github.com/PaulThblt)

# Requirements

RayBeam requires the following to function:
- a C++17 compiler
- pkg-config
- SFML 2.x
- libconfig++

SFML 3 changed several APIs used by this project, so install SFML 2.x unless you also update the source code.

# Setup

## macOS

Install dependencies with Homebrew:
```
brew install libconfig sfml@2 pkg-config
```

Then build:
```
make
```

`sfml@2` is keg-only in Homebrew, so it is not globally linked into `/opt/homebrew` or `/usr/local`. The Makefile detects `sfml@2` through `brew --prefix sfml@2` and passes the right `pkg-config` path automatically.

## Ubuntu / Debian

Install dependencies:
```
sudo apt update
sudo apt install build-essential pkg-config libsfml-dev libconfig++-dev
```

Then build:
```
make
```

## Fedora

Install dependencies:
```
sudo dnf install gcc-c++ make pkgconf-pkg-config SFML-devel libconfig-devel
```

Then build:
```
make
```

## Arch Linux

Install dependencies:
```
sudo pacman -S base-devel pkgconf sfml libconfig
```

Then build:
```
make
```

# Usage

To start the simulation:
```
./RayBeam
```
Run the binary from the repository root so it can find `scenes/`, `font.ttf`, and `rtx.png`.

Controls:
```
WASD: camera movement
ESCAPE or RETURN: exit simulation
```
To configure the scene, see [Documentation for Raytracer configuration files](./docs/Raytracer.pdf)

> [!NOTE]
> This project is no longer being maintained, but any improvements are welcome.
