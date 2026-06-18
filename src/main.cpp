#include "config/config.hpp"
#include "game/game.hpp"
#include "snake/snake.hpp"

int main() {
  Configuration config{get_configuration()};

  Game game(config);
  Snake snake {game.start()};
  game.redraw(snake);

  while (game.isRunning()) {
    game.handleInput();
    game.update_state(snake);
    game.redraw(snake);
    game.wait();
  }

  return 0;
}
