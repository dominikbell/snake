#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Configuration {
  unsigned int m_grid_height;
  unsigned int m_grid_width;
  float m_pixels_per_cell;  // for conversion from grid cell to pixels
  unsigned int m_game_speed;  // time step size in ms
  bool m_reflective;

  float grid_to_pixels(const unsigned int grid) {
    return static_cast<float>(grid) * m_pixels_per_cell;
  }
};

Configuration get_configuration();
json open_file();
