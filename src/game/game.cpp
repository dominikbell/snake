#include "game.hpp"

#include <chrono>
#include <iostream>
#include <optional>
#include <random>
#include <thread>
#include <vector>

#include "config/config.hpp"
#include "snake/snake.hpp"

Segment make_head(const Configuration& config) {
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<unsigned int> gen_width(2, config.m_grid_height);
  std::uniform_int_distribution<unsigned int> gen_height(2, config.m_grid_height);
  unsigned int start_x = gen_width(engine);
  unsigned int start_y = gen_height(engine);

  std::cout << "Start position is: (" << start_x << ", " << start_y << ").\n";

  return {start_x, start_y};
}

std::vector<Segment> make_body(const Segment& head) {
  std::vector<Segment> body;
  Segment new_part {head};
  for (unsigned int k = 0; k < 3; k++) {
    new_part.x = head.x + k;
    body.push_back(new_part);
  }

  return body;
}

Snake Game::start() {
  m_window.create(sf::VideoMode({m_config.m_window_width, m_config.m_window_height}), "Snake Game");
  m_isRunning = true;

  // Customize head of the snake
  m_head_block.setFillColor(sf::Color::Green);
  m_head_block.setOutlineColor(sf::Color::White);
  m_head_block.setOutlineThickness(1.0f);

  // Customize body block of the snake
  m_body_block.setFillColor(sf::Color::Yellow);
  m_body_block.setOutlineColor(sf::Color::White);
  m_body_block.setOutlineThickness(0.5f);

  // Make head and body of the snake
  Segment head {make_head(m_config)};
  std::vector<Segment> body {make_body(head)};

  return {1, Direction::LEFT, head, body};
}

void Game::update_state(Snake& snake) { std::cout << "One game step.\n"; }

void Game::redraw(const Snake& snake) {
  m_window.clear();

  m_head_block.setPosition({static_cast<float>(snake.m_head.x), static_cast<float>(snake.m_head.y)});
  m_window.draw(m_head_block);

  for (Segment body_block : snake.m_body) {
    m_body_block.setPosition({static_cast<float>(body_block.x), static_cast<float>(body_block.y)});
    m_window.draw(m_body_block);
  }

  m_window.display();
}

void Game::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(m_config.m_game_speed));
}

void Game::handleInput() {
  while (const std::optional event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_isRunning = false;
      m_window.close();  // Good practice to close the window
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      switch (keyPressed->code) {
        case sf::Keyboard::Key::Up: {
          std::cout << "Pressed Up." << std::endl;
          break;
        }
        case sf::Keyboard::Key::Down: {
          std::cout << "Pressed Down." << std::endl;
          break;
        }
        case sf::Keyboard::Key::Left: {
          std::cout << "Pressed Left." << std::endl;
          break;
        }
        case sf::Keyboard::Key::Right: {
          std::cout << "Pressed Right." << std::endl;
          break;
        }
        default: {
        };
      }
    }
  }
}
