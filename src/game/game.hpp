#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "config/config.hpp"
#include "food/food.hpp"
#include "snake/snake.hpp"

struct Game {
  bool m_isRunning;
  Configuration m_config;
  sf::RenderWindow m_window;
  sf::RectangleShape m_head_block;
  sf::RectangleShape m_body_block;
  sf::RectangleShape m_food_shape;

  void start();
  void move_snake_head(Snake& snake);
  void update_state(Snake& snake, Food& food);
  void redraw(const Snake& snake, const Food& food);
  void wait();
  void handleInput(Snake& snake);
  void check_bite(const Snake& snake);

  bool isRunning() { return m_isRunning; }

  Game(const Configuration& config) {
    m_config = config;
  }

 private:
  void game_over() {
    std::cout << "Game over.\n";
    m_isRunning = false;
    wait();
    m_window.close();
  }
};
