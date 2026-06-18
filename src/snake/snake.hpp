#pragma once

#include <vector>

#include "utils/utils.hpp"

/* In order to move the snake we just move the head by one and replace it with the last body segment.
 * m_last_body_segment indicates which of the body segments is currently the last one.
 */
struct Snake {
  int m_length;  // Only counts the body segments
  Direction m_direction;
  Location m_head;
  std::vector<Location> m_body;
  int m_last_body_segment {0};  // Used to denote which body part is the last one

  Snake(
      int length,
      Direction direction,
      Location head,
      std::vector<Location> body) {
    m_length = length;
    m_direction = direction;
    m_head = head;
    m_body = body;
    m_last_body_segment = length - 1;
  }
};
