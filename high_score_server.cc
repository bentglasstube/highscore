#include "high_score_server.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

HighScoreServer::HighScoreServer() : Server(8420) {
  std::cerr << "Started high score server on localhost:8420" << std::endl;

  std::ifstream reader("scores.db");
  Score score;
  while (reader) {
    if (reader >> score) scores_[score.game].insert(score);
  }
}

void HighScoreServer::receive(Socket& client, const std::string& data) {
  std::istringstream input(data);
  std::ostringstream output;

  Score score;

  if (input >> score) {
    std::cerr << "Got score: " << score << std::endl;

    auto& game = scores_[score.game];
    game.insert(score);

    output << score.game << " " << game.size() << std::endl;
    for (const auto& score : game) {
      output << score << std::endl;
    }
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));

  client.send(output.str());
}

void HighScoreServer::shutdown() {
  std::ofstream writer("scores.db");

  for (const auto& game : scores_) {
    for (const auto& score: game.second) {
      writer << score << std::endl;
    }
  }

  std::cerr << "Shutting down" << std::endl;
}
