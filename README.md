# 📦 Cub3D

A 3D game engine written from scratch in C, rendering a textured first-person view of a 2D map through raycasting, the same technique that powered Wolfenstein 3D.

## 🌟 Highlights

* Real-time raycasting engine with textured walls
* Strict `.cub` map parser with full configuration validation
* Smooth player movement with collision detection
* Clean window and memory management, zero leaks under Valgrind

## ℹ️ Overview

Cub3D is a graphics project from the [42 School](https://42.fr) curriculum that introduces the foundations of computer graphics: framebuffer manipulation, event handling, and the math behind 3D projection from a 2D grid.

The engine casts one ray per screen column from the player's position, uses the DDA algorithm to find the nearest wall, then derives the wall's apparent height and textures it by sampling an XPM file. Floor and ceiling are filled with configurable solid colors.

We built it during our time at 42 Perpignan as our first real dive into graphics programming.

## ✍️ Authors

Made by [**Clément Travers**](https://github.com/ClementTvs) and [**Arthur Perez**](https://github.com/Arthur-PRZ), students at 42 Perpignan.

## 🚀 Usage

Launch the engine with any valid `.cub` map file:

```
./cub3D maps/example.cub
```

Move with `W` `A` `S` `D`, rotate the camera with `←` `→`, and quit with `ESC`.

## ⬇️ Installation

Clone the repository and build with `make`:

```
git clone https://github.com/ClementTvs/cub3d.git
cd cub3d
make
```

**Requirements:**
- Linux or macOS
- `gcc` or `clang`, `make`
- MiniLibX dependencies (`xorg`, `libxext-dev`, `zlib1g-dev` on Linux; XQuartz on macOS)

## 💭 Feedback and Contributing

Found a bug or have a suggestion? Open an issue on the [Issues tab](https://github.com/ClementTvs/cub3d/issues) — feedback is always welcome.

This is a school project and not actively maintained, but we are happy to discuss the implementation or answer questions about raycasting.
