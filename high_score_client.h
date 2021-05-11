#pragma once

#include "client.h"

#include "score.h"

class HighScoreClient : public Client {
  public:

    HighScoreClient(const std::string& hostname, const std::string& game);

    void submit(const std::string& name, uint32_t score);
    void get_scores() { submit("x", 0); }

    const ScoreSet& scores() const { return scores_; }

    enum class State { Ready, Waiting, Done, Error };

    bool ready() const { return state_ == State::Ready; }
    bool loading() const { return state_ == State::Waiting; }
    bool done() const { return state_ == State::Done; }
    bool failed() const { return state_ == State::Error; }

    void receive(const std::string& p) override;
    void error() override { state_ = State::Error; }

  private:

    static constexpr uint16_t kHighScorePort = 8420;

    std::string hostname_, game_;
    ScoreSet scores_;
    State state_;
};
