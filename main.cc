#include "game.h"

#include "high_score_screen.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void step(void* game) {
  static_cast<Game*>(game)->step();
}
#endif

int main(int, char**) {
  Game::Config config;

  config.graphics.title = "High Score Demo";
  config.graphics.width = 512;
  config.graphics.height = 448;
  config.graphics.scale = 2;
  config.graphics.fullscreen = false;

  Game game(config);
  Screen *start = new HighScoreScreen();

#ifdef __EMSCRIPTEN__
  game.start(start);
  emscripten_set_main_loop_arg(step, &game, 0, true);
#else
  game.loop(start);
#endif

  return 0;
}
