#pragma once

#include <map>

#include "server.h"

#include "score.h"

class HighScoreServer: public Server {
  public:

    HighScoreServer();
    ~HighScoreServer() {}

    void receive(Socket& client, const std::string& data) override;
    void shutdown() override;

  private:

    std::map<std::string, ScoreSet> scores_;
};
