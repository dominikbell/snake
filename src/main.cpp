#include "config/config.hpp"
#include "food/food.hpp"
#include "game/game.hpp"
#include "snake/snake.hpp"

int main() {
  Configuration config {get_configuration()};

  Game game(config);
  Snake snake {game.start()};
  Food food(config);
  game.redraw(snake);

  while (game.isRunning()) {
    game.handleInput(snake);
    game.update_state(snake, food);
    game.check_bite(snake);
    game.redraw(snake);
    game.wait();
  }

  return 0;
}
