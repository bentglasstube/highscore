#pragma once

#include "audio.h"
#include "graphics.h"
#include "screen.h"
#include "text.h"

#include "high_score_client.h"

class HighScoreScreen : public Screen {
  public:

    HighScoreScreen();

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;
    Screen* next_screen() const override { return nullptr; }

  private:

    Text text_;
    HighScoreClient client_;

};
