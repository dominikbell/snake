#include "config.hpp"

#include <cstdint>
#include <iostream>

Configuration get_configuration() {
  int grid_height {10};
  int user_grid_height {0};
  int grid_width {15};
  int user_grid_width {0};
  int game_speed {1000};
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

  uint32_t window_height {static_cast<uint32_t>(grid_height * 10)};
  uint32_t window_width {static_cast<uint32_t>(grid_width * 10)};

  std::cout << "Grid size: " << grid_width << " x " << grid_height << '\n';
  return {grid_height, grid_width, window_height, window_width, game_speed, reflective};
}
