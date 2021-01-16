#include "Sequence.h"

bool Sequence::empty() const { return !curr_len_; }

int Sequence::size() const { return curr_len_; }

int Sequence::insert(int pos, const ItemType &value) {
  if (size() < DEFAULT_MAX_ITEMS && pos >= 0 && pos <= size()) {
    for (int i = pos; i < size(); i++) {
      list_[i + 1] = list_[i];
    }
    list_[pos] = value;
    curr_len_++;
    return pos;
  }
  return -1;
}

int Sequence::insert(const ItemType &value) {
  for (int i = 0; i < curr_len_; i++) {
    if (value <= list_[i]) {
      return insert(i, value);
    }
  }
  return insert(size(), value);
}

bool Sequence::erase(int pos) {
  if (pos >= 0 && pos <= size()) {
    for (int i = pos; i < size(); i++) {
      list_[i] = list_[i + 1];
    }
    curr_len_--;
    return true;
  }
  return false;
}

int Sequence::remove(const ItemType &value) {
  int i = 0;
  while (i < curr_len_) {
    if (value == list_[i]) {
      erase(i);
    }
    i += (value == list_[i]);
  }
}

bool Sequence::get(int pos, ItemType &value) const {
  if (pos >= 0 && pos <= size()) {
    value = list_[pos];
    return true;
  }
  return false;
}

bool Sequence::set(int pos, const ItemType &value) {
  if (pos >= 0 && pos <= size()) {
    list_[pos] = value;
    return true;
  }
  return false;
}

int Sequence::find(const ItemType &value) const {
  for (int i = 0; i < curr_len_; i++) {
    if (list_[i] == value) {
      return i;
    }
  }
  return -1;
}

void Sequence::swap(Sequence &other) {
  const Sequence tmp = other;
  for (int i = 0; i < curr_len_; i++) {
    other.list_[i] = list_[i];
  }
  other.curr_len_ = curr_len_;
  curr_len_ = tmp.curr_len_;
  for (int i = 0; i < curr_len_; i++) {
    list_[i] = tmp.list_[i];
  }
}
