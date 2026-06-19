#include "game.hpp"

#include <chrono>
#include <optional>
#include <thread>
#include <vector>

#include "config/config.hpp"
#include "snake/snake.hpp"
#include "utils/utils.hpp"

void Game::setup_grid() {
  m_grid.setPrimitiveType(sf::PrimitiveType::Lines);

  sf::Color lightGrey(211, 211, 211, 100);  // RGB + Alpha (100 out of 255 for transparency)

  float dashLength = 4.0f;
  float gapLength = 4.0f;

  float window_height {m_config.grid_to_pixels(m_config.m_grid_height)};
  float window_width {m_config.grid_to_pixels(m_config.m_grid_width)};

  // --- Draw Vertical Grid Lines ---
  for (int col = 1; col < m_config.m_grid_width; ++col) {
    float x = col * m_config.m_pixels_per_cell;
    float y = 0.0f;

    while (y < window_height) {
      // Segment start
      m_grid.append(sf::Vertex({x, y}, lightGrey));

      y += dashLength;
      if (y > window_height) y = window_height;

      // Segment end
      m_grid.append(sf::Vertex({x, y}, lightGrey));

      y += gapLength;  // Skip the gap
    }
  }

  // --- Draw Horizontal Grid Lines ---
  for (int row = 1; row < m_config.m_grid_height; ++row) {
    float y = row * m_config.m_pixels_per_cell;
    float x = 0.0f;

    while (x < window_width) {
      // Segment start
      m_grid.append(sf::Vertex({x, y}, lightGrey));

      x += dashLength;
      if (x > window_width) x = window_width;

      // Segment end
      m_grid.append(sf::Vertex({x, y}, lightGrey));

      x += gapLength;  // Skip the gap
    }
  }
}

void Game::start() {
  // Have to do this because window size is in unsigned int but everything else is in floats...
  unsigned int window_width {static_cast<unsigned int>(m_config.m_pixels_per_cell) * m_config.m_grid_width};
  unsigned int window_height {static_cast<unsigned int>(m_config.m_pixels_per_cell) * m_config.m_grid_height};

  m_window.create(sf::VideoMode({window_width, window_height}), "Snake Game");
  m_isRunning = true;

  m_head_block.setSize(sf::Vector2f(m_config.m_pixels_per_cell * 0.9f, m_config.m_pixels_per_cell * 0.9f));
  m_body_block.setSize(sf::Vector2f(m_config.m_pixels_per_cell * 0.9f, m_config.m_pixels_per_cell * 0.9f));
  m_food_shape.setSize(sf::Vector2f(m_config.m_pixels_per_cell * 0.9f, m_config.m_pixels_per_cell * 0.9f));

  // Customize head of the snake
  m_head_block.setFillColor(sf::Color::Green);
  m_head_block.setOutlineColor(sf::Color::White);
  m_head_block.setOutlineThickness(1.0f);

  // Customize body block of the snake
  m_body_block.setFillColor(sf::Color::Yellow);
  m_body_block.setOutlineColor(sf::Color::White);
  m_body_block.setOutlineThickness(0.5f);

  // Customize food block
  m_food_shape.setFillColor(sf::Color::Red);
  m_food_shape.setOutlineColor(sf::Color::White);
  m_food_shape.setOutlineThickness(0.5f);

  setup_grid();
}

void Game::move_snake_head(Snake& snake) {
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

void check_eating(Snake& snake, Food& food) {
  if (snake.m_head.x == food.m_location.x && snake.m_head.y == food.m_location.y) {
    food.m_has_been_eaten = true;
    snake.m_has_eaten = true;
  }
}

void Game::update_state(Snake& snake, Food& food) {
  snake.update_direction(m_direction_input);

  if (snake.m_has_eaten) {
    // When adding a segment to the snake, keep the order
    for (size_t index = snake.m_length; index > snake.m_last_body_segment + 1; index--) {
      snake.m_body[index] = snake.m_body[index - 1];
    }
    snake.m_length += 1;
    snake.m_has_eaten = false;
    snake.m_body[snake.m_last_body_segment + 1] = snake.m_head;
  } else {
    snake.m_body[snake.m_last_body_segment] = snake.m_head;
    snake.m_last_body_segment -= 1;
    if (snake.m_last_body_segment < 0) {
      snake.m_last_body_segment += snake.m_length;
    }
  }

  move_snake_head(snake);

  check_eating(snake, food);
  if (food.m_has_been_eaten) {
    food.spawn(snake);
  }
}

void Game::redraw(const Snake& snake, const Food& food) {
  m_window.clear();

  // Draw grid
  if (m_config.m_show_grid) {
    m_window.draw(m_grid);
  }

  // Draw snake
  m_head_block.setPosition({m_config.grid_to_pixels(snake.m_head.x), m_config.grid_to_pixels(snake.m_head.y)});
  m_window.draw(m_head_block);

  for (size_t index = 0; index < snake.m_length; index++) {
    m_body_block.setPosition(
        {m_config.grid_to_pixels(snake.m_body[index].x),
         m_config.grid_to_pixels(snake.m_body[index].y)});
    m_window.draw(m_body_block);
  }

  // Draw food
  m_food_shape.setPosition({m_config.grid_to_pixels(food.m_location.x), m_config.grid_to_pixels(food.m_location.y)});
  m_window.draw(m_food_shape);

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
          m_direction_input = Direction::UP;
          break;
        }
        case sf::Keyboard::Key::W: {
          m_direction_input = Direction::UP;
          break;
        }
        case sf::Keyboard::Key::Down: {
          m_direction_input = Direction::DOWN;
          break;
        }
        case sf::Keyboard::Key::S: {
          m_direction_input = Direction::DOWN;
          break;
        }
        case sf::Keyboard::Key::Left: {
          m_direction_input = Direction::LEFT;
          break;
        }
        case sf::Keyboard::Key::A: {
          m_direction_input = Direction::LEFT;
          break;
        }
        case sf::Keyboard::Key::Right: {
          m_direction_input = Direction::RIGHT;
          break;
        }
        case sf::Keyboard::Key::D: {
          m_direction_input = Direction::RIGHT;
          break;
        }
        default: {
        };
      }
    }
  }
}

void Game::check_bite(const Snake& snake) {
  for (Location body_segment : snake.m_body) {
    if (snake.m_head.x == body_segment.x && snake.m_head.y == body_segment.y) {
      game_over();
    }
  }
}
