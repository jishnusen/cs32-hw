#include "Sequence.h"

#include <iostream>

int subsequence(const Sequence& seq1, const Sequence& seq2) {
  ItemType seq1_getter;
  ItemType seq2_getter;
  if (seq2.size() < 1) {
    return -1;
  }
  for (int i = 0; i <= seq1.size() - seq2.size(); i++) {
    seq1.get(i, seq1_getter);
    seq2.get(0, seq2_getter);
    if (seq1_getter == seq2_getter) {
      int j;
      for (j = 1; j < seq2.size(); j++) {
        seq1.get(i + j, seq1_getter);
        seq2.get(j, seq2_getter);
        if (seq1_getter != seq2_getter) {
          break;
        }
      }
      if (j == seq2.size()) return i;
    }
  }
  return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
  ItemType dummy;
  while (result.get(0, dummy)) {
    result.erase(0);
  }

  const Sequence& bigger = seq1.size() >= seq2.size() ? seq1 : seq2;
  const Sequence& smaller = seq2.size() <= seq1.size() ? seq2 : seq1;

  ItemType s1_getter;
  ItemType s2_getter;

  for (int i = 0; i < smaller.size(); i++) {
    seq1.get(i, s1_getter);
    seq2.get(i, s2_getter);
    result.insert(result.size(), s1_getter);
    result.insert(result.size(), s2_getter);
  }

  ItemType b_getter;
  for (int i = smaller.size(); i < bigger.size(); i++) {
    bigger.get(i, b_getter);
    result.insert(result.size(), b_getter);
  }
}

Sequence::Sequence() : head_(nullptr) {}

Sequence::~Sequence() {
  ListNode* after;
  ListNode* traverse = head_;
  while (traverse != nullptr) {
    after = traverse->next;
    delete traverse;
    traverse = after;
  }
}

Sequence::Sequence(const Sequence& obj) {
  head_ = nullptr;
  if (obj.head_ == nullptr) {
    return;
  }
  head_ = new ListNode();
  head_->val = obj.head_->val;
  ListNode* traverse = head_;
  ListNode* obj_traverse = obj.head_->next;
  if (obj_traverse == nullptr) {
    return;
  }

  while (obj_traverse != nullptr) {
    ListNode* tmp = new ListNode();
    tmp->prev = traverse;
    tmp->val = obj_traverse->val;
    traverse->next = tmp;
    traverse = tmp;
    obj_traverse = obj_traverse->next;
  }
}

Sequence& Sequence::operator=(const Sequence& obj) {
  deleteList();
  if (obj.head_ == nullptr) {
    return *this;
  }
  head_ = new ListNode();
  head_->val = obj.head_->val;
  ListNode* traverse = head_;
  ListNode* obj_traverse = obj.head_->next;
  if (obj_traverse == nullptr) {
    return *this;
  }

  while (obj_traverse != nullptr) {
    ListNode* tmp = new ListNode();
    tmp->prev = traverse;
    tmp->val = obj_traverse->val;
    traverse->next = tmp;
    traverse = tmp;
    obj_traverse = obj_traverse->next;
  }
  return *this;
}

void Sequence::deleteList() {
  ListNode* after;
  ListNode* traverse = head_;
  while (traverse != nullptr) {
    after = traverse->next;
    delete traverse;
    traverse = after;
  }
  head_ = nullptr;
}

bool Sequence::empty() const { return head_ == nullptr; }

int Sequence::size() const {
  ListNode* traverse = head_;
  int cnt = 0;
  while (traverse != nullptr) {
    traverse = traverse->next;
    cnt++;
  }
  return cnt;
}

int Sequence::insert(int pos, const ItemType& value) {
  if (pos > size() || pos < 0) {
    return -1;
  }
  if (size() == 0) {
    head_ = new ListNode({nullptr, nullptr, value});
    return pos;
  }
  if (pos == 0) {
    ListNode* old_head = head_;
    head_ = new ListNode({nullptr, old_head, value});
    old_head->prev = head_;
    return pos;
  }
  ListNode* traverse = get_ptr_to_index(pos - 1);
  ListNode* after = traverse->next;

  ListNode* insertion = new ListNode({traverse, after, value});
  traverse->next = insertion;
  if (after != nullptr) {
    after->prev = insertion;
  }
  return pos;
}

int Sequence::insert(const ItemType& value) {
  ItemType getter;
  for (int i = 0; i < size(); i++) {
    get(i, getter);
    if (value <= getter) {
      return insert(i, value);
    }
  }
  return insert(size(), value);
}

bool Sequence::erase(int pos) {
  if (pos >= size() || pos < 0 || size() == 0) {
    return false;
  }

  if (pos == 0) {
    ListNode* new_head = head_->next;
    if (new_head != nullptr) new_head->prev = nullptr;
    ListNode* tmp = head_;
    delete tmp;
    head_ = new_head;
    return true;
  }
  ListNode* traverse = get_ptr_to_index(pos);
  ListNode* before = traverse->prev;
  ListNode* after = traverse->next;

  delete traverse;
  if (before != nullptr) {
    before->next = after;
  }
  if (after != nullptr) {
    after->prev = before;
  }
  return true;
}

int Sequence::remove(const ItemType& value) {
  int i = find(value);
  int cnt = 0;
  while (i != -1) {
    erase(i);
    i = find(value);
    cnt++;
  }
  return cnt;
}

bool Sequence::get(int pos, ItemType& value) const {
  if (pos >= size() || pos < 0 || size() == 0) {
    return false;
  }
  ListNode* traverse = get_ptr_to_index(pos);
  value = traverse->val;
  return true;
}

bool Sequence::set(int pos, const ItemType& value) {
  if (pos >= size() || pos < 0 || size() == 0) {
    return false;
  }
  ListNode* traverse = get_ptr_to_index(pos);
  traverse->val = value;
  return true;
}

int Sequence::find(const ItemType& value) const {
  int i = 0;
  ListNode* traverse = head_;
  while (traverse != nullptr) {
    if (traverse->val == value) {
      return i;
    }
    traverse = traverse->next;
    i++;
  }
  return -1;
}

Sequence::ListNode* Sequence::get_ptr_to_index(int pos) const {
  if (pos >= size() || pos < 0 || size() == 0) {
    return nullptr;
  }
  ListNode* traverse = head_;
  for (int i = 1; i <= pos; i++) {
    traverse = traverse->next;
  }
  return traverse;
}

void Sequence::swap(Sequence& other) {
  const Sequence tmp = *this;
  *this = other;
  other = tmp;
}

void Sequence::dump() const {
  ItemType value;
  for (int i = 0; i < size(); i++) {
    get(i, value);
    std::cerr << i << "\t" << value << std::endl;
  }
}
