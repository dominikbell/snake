#include "game.hpp"

#include <chrono>
#include <iostream>
#include <optional>
#include <thread>

Snake Game::start() {
  window.create(sf::VideoMode({m_config.m_window_width, m_config.m_window_height}), "Snake Game");
  window.clear();
  m_isRunning = true;

  sf::RectangleShape rectangle(sf::Vector2f(150.0f, 100.0f));

  // 3. Customize the rectangle
  rectangle.setFillColor(sf::Color::Green);             // Interior color
  rectangle.setOutlineColor(sf::Color::White);          // Border color
  rectangle.setOutlineThickness(5.0f);                  // Border thickness
  rectangle.setPosition(sf::Vector2f(325.0f, 250.0f));  // Position on screen (X, Y)

  window.draw(rectangle);
  window.display();

  return {1, Direction::LEFT};
}

void Game::update_state(Snake& snake) { std::cout << "One game step.\n"; }

void Game::redraw() {}

void Game::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(m_config.m_game_speed));
}

void Game::handleInput() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_isRunning = false;
      window.close();  // Good practice to close the window
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
        default:
      }
    }
  }
}
