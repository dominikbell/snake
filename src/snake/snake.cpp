#include "snake.hpp"

#include <random>
#include <iostream>

Location Snake::make_head(const Configuration& config) {
  std::random_device rd;
  std::mt19937 engine(rd());

  // start at 2 an subtract 2 (adjust width because body has some length) so snake doesn't start at the edge
  // TODO: make start direction random
  std::uniform_int_distribution<int> gen_width(2, config.m_grid_width - 2 - config.start_length);
  std::uniform_int_distribution<int> gen_height(2, config.m_grid_height - 2);

  int start_x = gen_width(engine);
  int start_y = gen_height(engine);

  std::cout << "Start position is: (" << start_x << ", " << start_y << ").\n";

  return {start_x, start_y};
}

std::vector<Location> Snake::make_body(const Configuration& config, const Location& head) {
  std::vector<Location> body {};
  body.resize(config.m_grid_height * config.m_grid_width);

  Location new_part;

  // Because start direction is left
  // TODO: make start direction random
  new_part.y = head.y;
  for (int k = 0; k < config.start_length; k++) {
    new_part.x = head.x + k + 1;
    body[k] = new_part;
  }

  return body;
}
