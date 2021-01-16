#include "ScoreList.h"

bool ScoreList::add(unsigned long score) {
  if (score <= 100) {
    return scores_.insert(score) != -1;
  }
  return false;
}

bool ScoreList::remove(unsigned long score) {
  return scores_.erase(scores_.find(score));
}

int ScoreList::size() const { return scores_.size(); }

unsigned long ScoreList::minimum() const {
  unsigned long ret = NO_SCORE;
  scores_.get(0, ret);
  return ret;
};

unsigned long ScoreList::maximum() const {
  unsigned long ret = NO_SCORE;
  scores_.get(scores_.size() - 1, ret);
  return ret;
}
