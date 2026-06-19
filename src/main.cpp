#include "config/config.hpp"
#include "food/food.hpp"
#include "game/game.hpp"
#include "snake/snake.hpp"

int main() {
  Configuration config {get_configuration()};

  Game game {config};
  Snake snake {config};
  Food food {config};

  game.start();
  food.spawn(snake);
  game.redraw(snake, food);

  while (game.isRunning()) {
    game.handleInput();
    game.update_state(snake, food);
    game.check_bite(snake);
    game.redraw(snake, food);
    game.wait();
  }

  return 0;
}
