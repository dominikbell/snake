#include "game.hpp"

#include <chrono>
#include <optional>
#include <random>
#include <thread>
#include <vector>

#include "config/config.hpp"
#include "snake/snake.hpp"

Segment make_head(const Configuration& config) {
  std::random_device rd;
  std::mt19937 engine(rd());

  // start at 2 an subtract 2 (4 for width because body has some length) so snake doesnt start at the edge
  std::uniform_int_distribution<int> gen_width(2, config.m_grid_width - 2 - config.start_length);
  std::uniform_int_distribution<int> gen_height(2, config.m_grid_height - 2);

  int start_x = gen_width(engine);
  int start_y = gen_height(engine);

  std::cout << "Start position is: (" << start_x << ", " << start_y << ").\n";

  return {start_x, start_y};
}

std::vector<Segment> make_body(const Configuration& config, const Segment& head) {
  std::vector<Segment> body;
  Segment new_part {head};
  for (int k = 0; k < config.start_length; k++) {
    new_part.x = head.x + k + 1;
    body.push_back(new_part);
  }

  return body;
}

Snake Game::start() {
  // Have to do this because window size is in unsigned int but everything else is in floats...
  unsigned int window_width {static_cast<unsigned int>(m_config.m_pixels_per_cell) * m_config.m_grid_width};
  unsigned int window_height {static_cast<unsigned int>(m_config.m_pixels_per_cell) * m_config.m_grid_height};

  m_window.create(sf::VideoMode({window_width, window_height}), "Snake Game");
  m_isRunning = true;

  m_head_block.setSize(sf::Vector2f(m_config.m_pixels_per_cell * 0.9f, m_config.m_pixels_per_cell * 0.9f));
  m_body_block.setSize(sf::Vector2f(m_config.m_pixels_per_cell * 0.9f, m_config.m_pixels_per_cell * 0.9f));

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
  std::vector<Segment> body {make_body(m_config, head)};

  return {m_config.start_length, Direction::LEFT, head, body};
}

void Game::update_state(Snake& snake) {
  snake.m_body[snake.m_last_body_segment] = snake.m_head;
  snake.m_last_body_segment -= 1;
  if (snake.m_last_body_segment < 0) {
    snake.m_last_body_segment += snake.m_length;
  }
  switch (snake.m_direction) {
    case Direction::LEFT: {
      snake.m_head.x -= 1;
      if (snake.m_head.x < 0) {
        if (m_config.m_periodic) {
          snake.m_head.x += m_config.m_grid_width;
        } else {
          game_over();
        }
      }
      break;
    }
    case Direction::RIGHT: {
      snake.m_head.x += 1;
      if (snake.m_head.x >= m_config.m_grid_width) {
        if (m_config.m_periodic) {
          snake.m_head.x -= m_config.m_grid_width;
        } else {
          game_over();
        }
      }
      break;
    }
    case Direction::UP: {
      snake.m_head.y -= 1;
      if (snake.m_head.y < 0) {
        if (m_config.m_periodic) {
          snake.m_head.y += m_config.m_grid_height;
        } else {
          game_over();
        }
      }
      break;
    }
    case Direction::DOWN: {
      snake.m_head.y += 1;
      if (snake.m_head.y >= m_config.m_grid_height) {
        if (m_config.m_periodic) {
          snake.m_head.y -= m_config.m_grid_height;
        } else {
          game_over();
        }
      }
      break;
    }
  }
}

void Game::redraw(const Snake& snake) {
  m_window.clear();

  m_head_block.setPosition({m_config.grid_to_pixels(snake.m_head.x), m_config.grid_to_pixels(snake.m_head.y)});
  m_window.draw(m_head_block);

  for (Segment body_block : snake.m_body) {
    m_body_block.setPosition({m_config.grid_to_pixels(body_block.x), m_config.grid_to_pixels(body_block.y)});
    m_window.draw(m_body_block);
  }

  m_window.display();
}

void Game::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(m_config.m_game_speed));
}

void Game::handleInput(Snake& snake) {
  while (const std::optional event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_isRunning = false;
      m_window.close();  // Good practice to close the window
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      switch (keyPressed->code) {
        case sf::Keyboard::Key::Up: {
          if (snake.m_direction != Direction::DOWN) {
            snake.m_direction = Direction::UP;
          }
          break;
        }
        case sf::Keyboard::Key::Down: {
          if (snake.m_direction != Direction::UP) {
            snake.m_direction = Direction::DOWN;
          }
          break;
        }
        case sf::Keyboard::Key::Left: {
          if (snake.m_direction != Direction::RIGHT) {
            snake.m_direction = Direction::LEFT;
          }
          break;
        }
        case sf::Keyboard::Key::Right: {
          if (snake.m_direction != Direction::LEFT) {
            snake.m_direction = Direction::RIGHT;
          }
          break;
        }
        default: {
        };
      }
    }
  }
}

void Game::check_bite(const Snake& snake) {
  for (Segment body_segment : snake.m_body) {
    if (snake.m_head.x == body_segment.x && snake.m_head.y == body_segment.y) {
      game_over();
    }
  }
}
