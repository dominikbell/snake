#pragma once

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

struct Snake {
  int m_length;
  Direction m_direction;
};
