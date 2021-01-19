#include "newSequence.h"

Sequence::Sequence()
    : list_(new ItemType[DEFAULT_MAX_ITEMS]), max_size_(DEFAULT_MAX_ITEMS) {}

Sequence::Sequence(int size) : list_(new ItemType[size]), max_size_(size) {}

Sequence::~Sequence() { delete[] list_; }

Sequence::Sequence(const Sequence &obj) {
  max_size_ = obj.max_size_;
  size_ = obj.size_;

  list_ = new ItemType[obj.max_size_];
  for (int i = 0; i < obj.size_; i++) {
    list_[i] = obj.list_[i];
  }
}

Sequence &Sequence::operator=(const Sequence &obj) {
  delete[] list_;

  max_size_ = obj.max_size_;
  size_ = obj.size_;

  list_ = new ItemType[obj.max_size_];
  for (int i = 0; i < obj.size_; i++) {
    list_[i] = obj.list_[i];
  }
  return *this;
}

bool Sequence::empty() const { return !size_; }

int Sequence::size() const { return size_; }

int Sequence::insert(int pos, const ItemType &value) {
  if (size() < max_size_ && pos >= 0 && pos <= size()) {
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
