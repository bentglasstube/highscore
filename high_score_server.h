#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#include "server.h"

class HighScoreServer: public Server {
  public:

    HighScoreServer();
    ~HighScoreServer() {}

    void receive(Socket& client, const std::string& data) override;
    void shutdown() override;

    struct Score {
      std::string game, name;
      uint32_t score;
    };

  private:

    std::map<std::string, std::vector<Score>> scores_;

    void load_scores();
};

std::ostream& operator<<(std::ostream& out, const HighScoreServer::Score& score);
std::istream& operator>>(std::istream& in, HighScoreServer::Score& score);
