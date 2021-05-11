#include <SDL2/SDL.h>

#include <iostream>

#include "high_score_server.h"

int main(int, char**) {
  HighScoreServer server;
  server.loop();
  return 0;
}
