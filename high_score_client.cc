#include "high_score_client.h"

#include <sstream>

HighScoreClient::HighScoreClient(const std::string& hostname, const std::string& game) :
  Client(hostname, kHighScorePort),
  hostname_(hostname), game_(game), state_(State::Ready) {}

void HighScoreClient::submit(const std::string& name, uint32_t score) {
  state_ = State::Waiting;
  Score s = { game_, name, score };
  send(s.to_string());
}

void HighScoreClient::receive(const std::string& data) {
  std::istringstream reader(data);
  Score score;

  std::string game;
  int count;

  reader >> game >> count;

  scores_.clear();
  while (reader) {
    if (reader >> score) scores_.insert(score);
  }

  state_ = State::Done;
}
