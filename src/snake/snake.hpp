#pragma once

#include <vector>

#include "config/config.hpp"
#include "utils/utils.hpp"

/* In order to move the snake we just move the head by one and replace it with the last body segment.
 * m_last_body_segment indicates which of the body segments is currently the last one.
 */
struct Snake {
  int m_length;  // Only counts the body segments
  Direction m_direction;
  bool m_has_eaten;
  Location m_head;
  std::vector<Location> m_body;
  int m_last_body_segment;  // Used to denote which body part is the last one

  void update_direction(const Direction new_direction) {
    switch (new_direction) {
      case Direction::LEFT: {
        if (m_direction != Direction::RIGHT) {
          m_direction = new_direction;
        }
        break;
      }
      case Direction::RIGHT: {
        if (m_direction != Direction::LEFT) {
          m_direction = new_direction;
        }
        break;
      }
      case Direction::UP: {
        if (m_direction != Direction::DOWN) {
          m_direction = new_direction;
        }
        break;
      }
      case Direction::DOWN: {
        if (m_direction != Direction::UP) {
          m_direction = new_direction;
        }
        break;
      }
    }
  }

  // TODO: make start direction random
  Snake(const Configuration& config)
      : m_length(config.m_start_length),
        m_direction(Direction::LEFT),
        m_has_eaten(false),
        m_last_body_segment(config.m_start_length - 1) {
    m_head = make_head(config);
    m_body = make_body(config, m_head);
  }

  private:
    Location make_head(const Configuration& config);
    std::vector<Location> make_body(const Configuration& config, const Location& head);
};
