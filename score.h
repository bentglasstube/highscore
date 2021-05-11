#pragma once

#include <iostream>
#include <vector>

struct Score {
  std::string game, name;
  uint32_t score;
  std::string to_string() const;
};

std::ostream& operator<<(std::ostream& out, const Score& score);
std::istream& operator>>(std::istream& in, Score& score);

class ScoreSet {
  public:
    typedef std::vector<Score>::iterator iterator;
    typedef std::vector<Score>::const_iterator const_iterator;
    typedef std::vector<Score>::reverse_iterator reverse_iterator;
    typedef std::vector<Score>::const_reverse_iterator const_reverse_iterator;

    Score& at(size_t pos) { return scores_.at(pos); }
    Score& operator[](size_t pos) { return scores_[pos]; }
    Score& front() { return scores_.front(); }
    Score& back() { return scores_.back(); }
    Score* data() { return scores_.data(); }

    const Score& at(size_t pos) const { return scores_.at(pos); }
    const Score& operator[](size_t pos) const { return scores_[pos]; }
    const Score& front() const { return scores_.front(); }
    const Score& back() const { return scores_.back(); }
    const Score* data() const { return scores_.data(); }

    iterator begin() { return scores_.begin(); }
    iterator end() { return scores_.end(); }

    reverse_iterator rbegin() { return scores_.rbegin(); }
    reverse_iterator rend() { return scores_.rend(); }

    const_iterator begin() const { return scores_.begin(); }
    const_iterator cbegin() const { return scores_.cbegin(); }
    const_iterator end() const { return scores_.end(); }
    const_iterator cend() const { return scores_.cend(); }

    const_reverse_iterator rbegin() const { return scores_.rbegin(); }
    const_reverse_iterator crbegin() const { return scores_.crbegin(); }
    const_reverse_iterator rend() const { return scores_.rend(); }
    const_reverse_iterator crend() const { return scores_.crend(); }

    bool empty() const { return scores_.empty(); }
    size_t size() const { return scores_.size(); }
    size_t max_size() const { return scores_.max_size(); }
    void reserve(size_t cap) { scores_.reserve(cap); }
    size_t capacity() const { return scores_.capacity(); }
    void shrink_to_fit() { scores_.shrink_to_fit(); }

    void clear() { scores_.clear(); }
    iterator erase(const_iterator pos) { return scores_.erase(pos); }
    iterator erase(const_iterator first, const_iterator last) { return scores_.erase(first, last); }

    iterator insert(const Score& s);

  private:
    std::vector<Score> scores_;
};
