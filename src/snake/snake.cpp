#include "snake.hpp"

#include <random>
#include <iostream>
#include "utils/utils.hpp"

Location Snake::make_head(const Configuration& config) {
  std::random_device rd;
  std::mt19937 engine(rd());

  // start and end with body length so snake doesn't start at the edge

  int start_x {0};
  int end_x {static_cast<int>(config.m_grid_width) - 1};
  int start_y {0};
  int end_y {static_cast<int>(config.m_grid_height) - 1};

  switch (m_direction) {
    case Direction::LEFT: {
      start_x += config.m_start_length;
      end_x -= config.m_start_length;
    break;
    }
    case Direction::RIGHT: {
      start_x += config.m_start_length;
      end_x -= config.m_start_length;
    break;
    }
    case Direction::UP: {
      start_y += config.m_start_length;
      end_y -= config.m_start_length;
    break;
    }
    case Direction::DOWN: {
      start_y += config.m_start_length;
      end_y -= config.m_start_length;
    break;
    }
  }

  std::uniform_int_distribution<int> gen_width(start_x, end_x);
  std::uniform_int_distribution<int> gen_height(start_y, end_y);

  int x = gen_width(engine);
  int y = gen_height(engine);

  std::cout << "Start position is: (" << x << ", " << y << ").\n";

  return {x, y};
}

std::vector<Location> Snake::make_body(const Configuration& config) {
  std::vector<Location> body {};
  body.resize(config.m_grid_height * config.m_grid_width);

  Location new_part {m_head};

  for (int k = 0; k < config.m_start_length; k++) {
    switch (m_direction) {
      case Direction::LEFT: {
        new_part.x = m_head.x + k + 1;
        break;
      }
      case Direction::RIGHT: {
        new_part.x = m_head.x - k - 1;
        break;
      }
      case Direction::UP: {
        new_part.y = m_head.y + k + 1;
        break;
      }
      case Direction::DOWN: {
        new_part.y = m_head.y - k - 1;
        break;
      }
    }
    body[k] = new_part;
  }

  return body;
}

Direction Snake::make_direction() {
  // Generate random initial direction
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<int> gen_direction(0, 3);
  int direction_int = gen_direction(engine);

  switch(direction_int) {
    case (0): return Direction::LEFT;
    case (1): return Direction::RIGHT;
    case (2): return Direction::UP;
    case (3): return Direction::DOWN;
    default: return Direction::LEFT;
  }
}
