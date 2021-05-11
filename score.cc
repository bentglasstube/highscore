#include "score.h"

std::string Score::to_string() const {
  return game + " " + name + " " + std::to_string(score);
}

std::ostream& operator<<(std::ostream& out, const Score& score) {
  out << score.game << " " << score.name << " " << score.score;
  return out;
}

std::istream& operator>>(std::istream& in, Score& score) {
  in >> score.game >> score.name >> score.score;
  return in;
}

ScoreSet::iterator ScoreSet::insert(const Score& score) {
  if (score.score == 0) return scores_.end();
  auto i = begin();
  for (; i != end(); ++i) {
    if (i->score < score.score) break;
  }
  return scores_.insert(i, score);
}

