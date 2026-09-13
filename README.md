*This project has been created as part of the 42 curriculum by sgadinga*

# FdF — Fil de Fer

A 3D wireframe renderer that reads a `.fdf` map and projects it as an
isometric wireframe, built as part of the 42 School curriculum using MiniLibX.

## Description

FdF takes a grid of altitude values from a `.fdf` file and renders the
corresponding 3D terrain as a wireframe. Points are mapped to 3D coordinates,
projected using parallel (isometric) projection, and drawn with the standard
line-drawing algorithm. The renderer supports colouring, rotation, zoom and
panning, all controlled interactively from the keyboard and mouse.

## Features

- **Map parsing** — reads rectangular grids of integer altitudes (plus
  optional per-point colours) from `.fdf` files.
- **Isometric projection** — computes rotation matrices and projects the 3D
  model onto the 2D screen.
- **Interactive controls** — zoom, pan, and rotation around the X, Y and Z axes
  bound to keyboard and mouse events, with an on-screen instructions overlay.
- **Colour handling** — gradient colouring between points based on altitude,
  plus per-point colours defined in the map file.
- Built on the author's own `libft` and MiniLibX (`minilibx-linux`).

## Requirements

- Linux OS
- `cc` and `make`
- X11 development libraries (required by MiniLibX)

```sh
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

## Build & usage

Clone the repository and initialise the MiniLibX submodule first:

```sh
git submodule update --init
make         # build fdf
make clean   # remove object files
make fclean  # remove object files and the binary
make re      # fclean + all
```

Run the program with a map file:

```sh
./fdf test_maps/42.fdf
./fdf test_maps/mars.fdf
```

## Repository structure

| File                    | Purpose                                   |
| ----------------------- | ----------------------------------------- |
| `src/fdf.c`             | Entry point and final render loop.        |
| `src/map.c`             | `.fdf` file parsing into the 3D grid.     |
| `src/render.c`          | Projection and frame rendering.           |
| `src/draw.c`            | Line drawing and rasterisation.           |
| `src/colors.c`          | Altitude-based colour gradients.          |
| `src/hooks.c`           | Keyboard and mouse event handling.        |
| `src/rotations.c`       | 3D rotation matrices.                     |
| `src/instruct.c`        | On-screen control instructions.           |
| `src/utils/`            | Drawing, hooks, map and render helpers.   |
| `test_maps/`            | Sample `.fdf` maps.                       |