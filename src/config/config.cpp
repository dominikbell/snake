#include "config.hpp"

#include <iostream>

Configuration get_configuration() {
  unsigned int grid_height {10};
  unsigned int user_grid_height {0};
  unsigned int grid_width {15};
  unsigned int user_grid_width {0};
  unsigned int game_speed {1000};
  bool reflective {false};

  if (false) {
    // Get grid_width from user, for invalid inputs default will be used
    std::cout << "Enter the preferred grid width (default is " << grid_width << ") \n";
    std::cin >> user_grid_width;
    if (user_grid_width) {
      grid_width = user_grid_width;
    }

    // Get grid_height from user, for invalid inputs default will be used
    std::cout << "Enter the preferred grid height (default is " << grid_height << ") \n";
    std::cin >> user_grid_height;
    if (user_grid_height) {
      grid_height = user_grid_height;
    }
  }

  unsigned int window_height {static_cast<unsigned int>(grid_height * 40)};
  unsigned int window_width {static_cast<unsigned int>(grid_width * 40)};

  std::cout << "Window size: " << window_height << " x " << window_width << '\n';
  return {grid_height, grid_width, window_height, window_width, game_speed, reflective};
}
