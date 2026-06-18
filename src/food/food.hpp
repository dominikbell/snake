#pragma once

#include <random>

#include "config/config.hpp"
#include "snake/snake.hpp"
#include "utils/utils.hpp"

struct Food {
  Location m_location;
  std::random_device rd;
  std::mt19937 m_engine {rd()};
  std::uniform_int_distribution<int> m_gen_width;
  std::uniform_int_distribution<int> m_gen_height;

  void spawn(const Snake& snake);

  Food(const Configuration& config) {
    std::uniform_int_distribution<int> m_gen_width(0, config.m_grid_width);
    std::uniform_int_distribution<int> m_gen_height(0, config.m_grid_height);
  }

 private:
  bool colliding(const Snake& snake) {
    if (m_location.x == snake.m_head.x && m_location.y == snake.m_head.y) {
      return true;
    }
    for (Location body_segment : snake.m_body) {
      if (m_location.x == body_segment.x && m_location.y == body_segment.y) {
        return true;
      }
    }
    return false;
  }
};
