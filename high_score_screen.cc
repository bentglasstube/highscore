#include "high_score_screen.h"

#include <iomanip>
#include <sstream>

HighScoreScreen::HighScoreScreen() :
  text_("text.png"), client_("localhost", "test") {}

bool HighScoreScreen::update(const Input& input, Audio&, unsigned int) {
  client_.check();

  if (client_.ready()) client_.get_scores();

  return true;
}

void HighScoreScreen::draw(Graphics& graphics) const {
  text_.draw(graphics, "Congratulations!", graphics.width() / 2, 16, Text::Alignment::Center);
  text_.draw(graphics, "Enter your name below.", graphics.width() / 2, 32, Text::Alignment::Center);

  if (client_.done()) {
    int place = 0;
    for (const auto& s : client_.scores()) {
      std::ostringstream t;
      t << std::setfill(' ');
      t << std::setw(3) << (place + 1) << ". ";
      t << std::setw(3) << s.name << " ";
      t << std::setw(8) << s.score;

      const int tx = 8 + (place % 3) * 144;
      const int ty = 64 + (place / 3) * 16;

      text_.draw(graphics, t.str(), tx, ty);

      if (++place >= 20 * 3) break;
    }
  } else if (client_.loading()) {
    text_.draw(graphics, "Connecting to high score server...", graphics.width() / 2, 64, Text::Alignment::Center);
  } else if (client_.failed()) {
    text_.draw(graphics, "Failed to get high scores.", graphics.width() / 2, 64, Text::Alignment::Center);
  }
}
