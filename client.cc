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

  client.get_scores();
  while (client.loading()) {
    client.check();
  }

  for (auto const& s : client.scores()) {
    std::cout << s << std::endl;
  }

  std::random_device rd;
  std::mt19937 rng(rd());

  const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 1);
  auto randchar = [ charset, &dist, &rng ](){ return charset[dist(rng)]; };

  std::string name = random_string(3, randchar);
  uint32_t score = std::uniform_int_distribution<uint32_t>(0, 10000)(rng);

  std::cout << "Submitting new score: " << name << ": " << score << std::endl;
  client.submit(name, score);

  while (client.loading()) {
    client.check();
  }

  if (client.failed()) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "Success" << std::endl;

    for (auto const& s : client.scores()) {
      std::cout << s << std::endl;
    }
  }

  return 0;
}
