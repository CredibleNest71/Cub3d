# cub3D

A first-person 3D maze in the style of Wolfenstein 3D, rendered with raycasting in C and MiniLibX. Team project at 42 Vienna.

![cub3D gameplay](cub3d.gif)

## Features

- Raycasting engine: one ray per screen column, with separate checks for horizontal and vertical grid lines, then the nearest hit is drawn
- Textured walls with a different texture for each direction (north, south, east, west)
- Floor and ceiling colours from the map file
- Smooth movement with collision detection, so you can't walk through walls
- Mouse look, sprinting and an adjustable field of view
- Map parser with validation: checks the file extension, textures, colours, the player start and that the map is closed by walls

## Build and run

Requires MiniLibX for Linux and the X11 development libraries (`libx11-dev`, `libxext-dev`).

```sh
make
./cub3D maps/good.cub
```

Try `maps/drunk.cub` for a level with bar-themed textures.

## Controls

| Key | Action |
| --- | --- |
| `W` `A` `S` `D` | Move and strafe |
| `←` `→` or mouse | Turn |
| `Shift` | Sprint |
| `Q` / `E` | Narrow / widen the field of view |
| `Esc` | Quit |

## Map format

```
NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 199,220,227
C 149,226,250

111111
100001
10N001
111111
```

`1` = wall, `0` = floor, `N`/`S`/`E`/`W` = player start and viewing direction. `F` and `C` set the floor and ceiling colours (RGB).

## Structure

```
Parsing/       reading and validating the .cub file
CastingRays/   raycasting
Display/       drawing walls, textures, floor and ceiling
Movement/      player movement, rotation and collision
Initialize/    window, hooks and input
Cleaning/      freeing memory on exit
```

## Team

Melih Senyurt and Moritz Resch.

My part: player movement and collision, texture rendering, and parts of the raycaster and the map parser.
