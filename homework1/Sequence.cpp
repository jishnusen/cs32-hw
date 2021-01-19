#include "Sequence.h"

bool Sequence::empty() const { return !size_; }

int Sequence::size() const { return size_; }

int Sequence::insert(int pos, const ItemType &value) {
  if (size() < DEFAULT_MAX_ITEMS && pos >= 0 && pos <= size()) {
    for (int i = size(); i > pos; i--) {
      list_[i] = list_[i - 1];
    }
    list_[pos] = value;
    size_++;
    return pos;
  }
  return -1;
}

int Sequence::insert(const ItemType &value) {
  for (int i = 0; i < size_; i++) {
    if (value <= list_[i]) {
      return insert(i, value);
    }
  }
  return insert(size(), value);
}

bool Sequence::erase(int pos) {
  if (pos >= 0 && pos <= size()) {
    for (int i = pos; i + 1 < size(); i++) {
      list_[i] = list_[i + 1];
    }
    size_--;
    return true;
  }
  return false;
}

int Sequence::remove(const ItemType &value) {
  int i = find(value);
  int cnt = 0;
  while (i != -1) {
    erase(i);
    i = find(value);
    cnt++;
  }
  return cnt;
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
  for (int i = 0; i < size_; i++) {
    if (list_[i] == value) {
      return i;
    }
  }
  return -1;
}

void Sequence::swap(Sequence &other) {
  const Sequence tmp = *this;
  *this = other;
  other = tmp;
}
