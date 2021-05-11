#include "high_score_server.h"

HighScoreServer::HighScoreServer() : Server(8420) {
  std::cerr << "Started high score server on localhost:8420" << std::endl;

  std::ifstream reader("scores.db");
  Score score;
  while (reader) {
    if (reader >> score) scores_[score.game].push_back(score);
  }
}

void HighScoreServer::receive(Socket& client, const std::string& data) {
  std::istringstream input(data);
  std::ostringstream output;

  Score score;
  if (input >> score) {
    auto& game = scores_[score.game];

    if (score.score > 0) {
      auto it = game.begin();
      for (; it != game.end(); ++it) {
        if (it->score < score.score) break;
      }
      game.insert(it, score);
    }

    for (const auto& score : game) {
      output << score << std::endl;
    }
  }

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

std::ostream& operator<<(std::ostream& out, const HighScoreServer::Score& score) {
  out << score.game << " " << score.name << " " << score.score;
  return out;
}

std::istream& operator>>(std::istream& in, HighScoreServer::Score& score) {
  in >> score.game >> score.name >> score.score;
  return in;
}
