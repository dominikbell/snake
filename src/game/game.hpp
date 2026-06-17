#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "config/config.hpp"

struct Game {
  bool m_isRunning;
  Configuration m_config;
  sf::RenderWindow window;

  void start();
  void update_state();
  void redraw();
  void wait();

  bool isRunning() { return m_isRunning; }

  Game(const Configuration& config) {
    m_config = config;
  }

 private:
  void handleInput();
};
