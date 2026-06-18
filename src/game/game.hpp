#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "config/config.hpp"
#include "snake/snake.hpp"

struct Game {
  bool m_isRunning;
  Configuration m_config;
  sf::RenderWindow m_window;
  sf::RectangleShape m_head_block{sf::Vector2f(20.0f, 20.0f)};
  sf::RectangleShape m_body_block{sf::Vector2f(20.0f, 20.0f)};

  Snake start();
  void update_state(Snake& snake);
  void redraw(const Snake& snake);
  void wait();
  void handleInput();

  bool isRunning() { return m_isRunning; }

  Game(const Configuration& config) {
    m_config = config;
  }
};
