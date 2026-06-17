#include "config/config.hpp"
#include "game/game.hpp"

int main() {
  Configuration config{get_configuration()};

  Game game(config);
  game.start();

  while (game.isRunning()) {
    game.update_state();
    game.redraw();
    game.wait();
  }

  return 0;
}
