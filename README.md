# Cub3D

<p align="center" width="100%">
    <img width="33%" src="https://github.com/Arcane-Jill/images/blob/main/cub3dm.png">
</p>

## Project overview

The project is a part of the [Hive Helsinki](https://www.hive.fi/en/curriculum) core curriculum. The goal of **Cub3D** is to develop a 3D game engine from scratch using raycasting. We simulate a 3D environment where players can navigate through a maze.
This project was developed by [Natalie Meintjes](https://github.com/natalie-mein) and [Martin Dahlström](https://github.com/mdheuser))as part of the 42 core curriculum.

## Features

### Rendering
Raycasting is achieved through rendereing a 3D world from a 2D map.
There are also textures for walls, and floor and ceiling colours.

### Player movement
A player can move forward, backward and side to side using WSAD keys, as well as strafe with the '<' and '>' keys.
We also implemented wall collision detection to prevent players from moving through the walls.

## Installation
Clone the repository and make:
```
git clone git@github.com:natalie-mein/cubed3D.git cubed
cd cubed
make
```
Run the game:
```
./cub3d <map_file_name>
```

