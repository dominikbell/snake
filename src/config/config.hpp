#pragma once

#include <cstdint>

struct Configuration {
  int m_grid_height;
  int m_grid_width;
  uint32_t m_window_height;
  uint32_t m_window_width;
  int m_game_speed;  // time step size in ms
  bool m_reflective;
};

Configuration get_configuration();
