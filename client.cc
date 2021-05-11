#include "high_score_client.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>

std::string random_string(size_t length, std::function<char(void)> gen) {
  std::string str(length, 0);
  std::generate_n(str.begin(), length, gen);
  return str;
}

int main(int, char**) {
  HighScoreClient client("localhost", "test");

  if (client.connected()) {
    std::cout << "Connected!" << std::endl;

    for (auto const& s : client.scores()) {
      std::cout << s << std::endl;
    }
  } else {
    std::cout << "Couldn't connect" << std::endl;
  }

  std::random_device rd;
  std::mt19937 rng(rd());

  const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 1);
  auto randchar = [ charset, &dist, &rng ](){ return charset[dist(rng)]; };

  Score s {
    "test",
     random_string(3, randchar),
     std::uniform_int_distribution<uint32_t>(0, 10000)(rng)
  };

  std::cout << "Submitting new score: " << s << std::endl;
  if (client.submit(s)) {
    std::cout << "Success!" << std::endl;
  } else {
    std::cout << "Failed to submit score" << std::endl;
  }

  for (auto const& s : client.scores()) {
    std::cout << s << std::endl;
  }

  return 0;
}
