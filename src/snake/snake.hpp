#pragma once

#include <vector>
enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

struct Segment {
  unsigned int x;
  unsigned int y;
};

struct Snake {
  int m_length;
  Direction m_direction;
  Segment m_head;
  std::vector<Segment> m_body {};
};
