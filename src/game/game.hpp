#pragma once

#include "config/config.hpp"

struct Game {
  bool m_is_running;
  Configuration m_config;

  void start();
  void update_state();
  void redraw();
  void wait();

  Game(const Configuration& config) {
    m_config = config;
  }
};
