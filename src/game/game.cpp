#include "game.hpp"
#include <iostream>

#include <chrono>
#include <thread>

void Game::start() { m_is_running = true; }
void Game::update_state() { std::cout << "One game step.\n"; }
void Game::redraw() {};
void Game::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(m_config.m_game_speed));
}
