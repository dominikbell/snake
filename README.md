# snake

A simple snake game.

## Requirements

- [ ] [SFML](https://www.sfml-dev.org/) for GUI
- [ ] [`json` by nlohmann](https://github.com/nlohmann/json)


## Build and run

```
mkdir build
cd build
cmake ..
cmake --build .
./src/snake_game
```

The snake can be controlled with the arrow keys or WASD.

## Configuration

The game settings can be adjusted by changing the config file `config/config.json`. The following parameters can be set:

- `grid_width` : The width of the grid of the game (unsigned integer)
- `grid_height` : The width of the grid of the game (unsigned integer)
- `game_speed` : The speed of the game (double)
- `cell_size` : The size of the cells in pixels (float)
- `periodic` : If the walls should have periodic boundary conditions (boolean)
- `start_length` : The initial length of the snake (integer)
- `show_grid` : If grid lines should be shown (boolean)
