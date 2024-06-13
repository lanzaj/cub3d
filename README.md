# CUB3D

This project is a wolfenstein-like game coded in C using raycasting. No game engine was used.

![Alt Text](./readme/game.gif)

## Raycasting ?
Raycasting is a technique used in computer graphics to create a 3D-like perspective in a 2D game world. Imagine you are standing in a maze and you shine a flashlight straight ahead. The light beam is like a "ray" that travels until it hits a wall.

In raycasting, the game sends out many rays from the player's position, one for each column of pixels on the screen. Each ray moves forward until it hits an obstacle, like a wall. The distance each ray travels determines how tall the wall appears on the screen, creating the illusion of depth. Closer walls look taller, and farther walls look shorter.

Raycasting is efficient because it only calculates the visible walls and ignores everything else, making it a popular choice for early 3D games like "Wolfenstein 3D."

## Features

- Loads any `.cub` map (several examples can be found in `./maps` directory)
- Handles different colors for floor and ceiling, and different textures for walls according to their orientation
- Working doors
- Enemies
- Health kit to gain life points

## Getting Started (linux)

1. Clone the repository: `git clone https://github.com/tgrasset/cub3d.git`
2. Compile : `cd cub3d && make`
4. Launch
```console
./cub3D
```
or
```console
./cub3D <path/to/maps/file.cub>
```

## Usage

- Look around with left and right arrows or the mouse
- Move forward with up arrow or `W`
- Move backward with down arrow or `S`
- Move sideways with `A` and `D`
- Quit with `Escape`
- Open doors with `space`
- Shoot with `Ctrl` or `left click`
- Sprint with `Shift`
- Pause with `Tab`
- Show / Hide fps with `F`
- Show / Hide map with `M`


## Credits

Created with [mbocquel](https://github.com/mbocquel)

Textures :
- https://little-martian.itch.io/retro-sprite-pack

- https://wenrexa.itch.io/ui-different02

- https://imgur.com/nE5zw9q

- https://little-martian.itch.io/retro-texture-pack

- https://tinyworlds.itch.io/free-pixel-font-thaleah

Title screen generated with stable diffusion.
