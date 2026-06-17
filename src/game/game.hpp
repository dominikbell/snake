#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "config/config.hpp"
#include "snake/snake.hpp"

struct Game {
  bool m_isRunning;
  Configuration m_config;
  sf::RenderWindow window;

  Snake start();
  void update_state(Snake& snake);
  void redraw();
  void wait();
  void handleInput();

  bool isRunning() { return m_isRunning; }

  Game(const Configuration& config) {
    m_config = config;
  }
};
