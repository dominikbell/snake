#pragma once

#include <cstdint>

struct Configuration {
  unsigned int m_grid_height;
  unsigned int m_grid_width;
  unsigned int m_window_height;
  unsigned int m_window_width;
  unsigned int m_game_speed;  // time step size in ms
  bool m_reflective;
};

Configuration get_configuration();
