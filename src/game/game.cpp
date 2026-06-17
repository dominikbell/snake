#include "game.hpp"

#include <chrono>
#include <iostream>
#include <optional>
#include <thread>

void Game::start() {
  window.create(sf::VideoMode({m_config.m_window_width, m_config.m_window_height}), "Snake Game");
  m_isRunning = true;
}
void Game::update_state() { std::cout << "One game step.\n"; }
void Game::redraw() {
  handleInput();
}
void Game::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(m_config.m_game_speed));
}
void Game::handleInput() {
  std::cout << "handleInput is being called.\n";
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_isRunning = false;
      window.close();  // Good practice to close the window window
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
