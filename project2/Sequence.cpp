#include "Sequence.h"

#include <iostream>

int subsequence(const Sequence& seq1, const Sequence& seq2) {
  ItemType seq1_getter;
  ItemType seq2_getter;
  if (seq2.size() < 1) {
    return -1;
  }
  // loop only runs till remaining elements less than seq2 size
  for (int i = 0; i <= seq1.size() - seq2.size(); i++) {
    seq1.get(i, seq1_getter);
    seq2.get(0, seq2_getter);
    if (seq1_getter == seq2_getter) {  // elem i of seq1 vs elem 0 of seq2
      int j;
      for (j = 1; j < seq2.size(); j++) {
        seq1.get(i + j, seq1_getter);
        seq2.get(j, seq2_getter);
        if (seq1_getter != seq2_getter) {
          break;
        }
      }
      if (j == seq2.size()) return i;  // loop ran, all elements matched
    }
  }
  return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
  Sequence res = result;
  ItemType dummy;
  while (res.get(0, dummy)) {
    res.erase(0);
  }
  // longer seq
  const Sequence& bigger = seq1.size() >= seq2.size() ? seq1 : seq2;
  // shorter seq
  const Sequence& smaller = seq2.size() <= seq1.size() ? seq2 : seq1;

  ItemType s1_getter;
  ItemType s2_getter;

  // first alternate seq 1 and seq2
  for (int i = 0; i < smaller.size(); i++) {
    seq1.get(i, s1_getter);
    seq2.get(i, s2_getter);
    res.insert(res.size(), s1_getter);
    res.insert(res.size(), s2_getter);
  }

  ItemType b_getter;
  // terminate with rem. longer seq
  for (int i = smaller.size(); i < bigger.size(); i++) {
    bigger.get(i, b_getter);
    res.insert(res.size(), b_getter);
  }
  result = res;
}

Sequence::Sequence() : head_(nullptr) {}

Sequence::~Sequence() {
  ListNode* after;
  ListNode* traverse = head_;
  // delete every element
  while (traverse != nullptr) {
    after = traverse->next;
    delete traverse;
    traverse = after;
  }
}

Sequence::Sequence(const Sequence& obj) {
  head_ = nullptr;
  if (obj.size() == 0) {  // empty by default
    return;
  }
  head_ = new ListNode();
  head_->val = obj.head_->val;  // deep copy first element
  ListNode* traverse = head_;
  ListNode* obj_traverse = obj.head_->next;  // one ahead of traverse
  if (obj_traverse == nullptr) {             // single element seq
    return;
  }

  while (obj_traverse != nullptr) {  // deep copy every remaining element
    ListNode* tmp = new ListNode();  // one ahead of travers
    tmp->prev = traverse;            // link to traverse
    tmp->val = obj_traverse->val;    // update with one ahead
    traverse->next = tmp;            // link to one ahead
    traverse = tmp;
    obj_traverse = obj_traverse->next;  // move forward one on target seq
  }
}

Sequence& Sequence::operator=(const Sequence& obj) {
  deleteList();  // delete list, then same as copy constructor
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

void Sequence::deleteList() {  // delete every element, but use copy for head_
  ListNode* after;
  ListNode* traverse = head_;
  while (traverse != nullptr) {
    after = traverse->next;
    delete traverse;
    traverse = after;
  }
  head_ = nullptr;  // keeps head_ alive
}

bool Sequence::empty() const { return head_ == nullptr; }

int Sequence::size() const {
  ListNode* traverse = head_;  // walks along list
  int cnt = 0;
  // while there are elements left to count, count them
  while (traverse != nullptr) {
    traverse = traverse->next;  // walk forward
    cnt++;
  }
  return cnt;
}

int Sequence::insert(int pos, const ItemType& value) {
  if (pos > size() || pos < 0) {
    return -1;
  }
  if (size() == 0) {  // insert to empty seq, new head_
    head_ = new ListNode({nullptr, nullptr, value});
    return pos;
  }
  if (pos == 0) {  // insert to start of seq, new head_, link old head_
    ListNode* old_head = head_;
    head_ = new ListNode({nullptr, old_head, value});
    old_head->prev = head_;
    return pos;
  }
  ListNode* traverse = get_ptr_to_index(pos - 1);  // get elem before target
  ListNode* after = traverse->next;                // element after target

  // new element, linked to before + after
  ListNode* insertion = new ListNode({traverse, after, value});
  traverse->next = insertion;  // link before
  if (after != nullptr) {      // if not at the end, link after
    after->prev = insertion;
  }
  return pos;
}

int Sequence::insert(const ItemType& value) {
  ItemType getter;
  for (int i = 0; i < size(); i++) {  // check every element
    get(i, getter);
    if (value <= getter) {  // insert before the first element that is bigger
      return insert(i, value);  // will move bigger elements after new element
    }
  }
  return insert(size(), value);  // otherwise insert at the end
}

bool Sequence::erase(int pos) {
  if (pos >= size() || pos < 0 || size() == 0) {  // if no elements, erase bad
    return false;
  }

  if (pos == 0) {  // if erasing element 1, delete and unlink head_
    ListNode* new_head = head_->next;
    if (new_head != nullptr) new_head->prev = nullptr;
    ListNode* tmp = head_;
    delete tmp;
    head_ = new_head;  // head_ is element after old head_ now
    return true;
  }
  ListNode* traverse = get_ptr_to_index(pos);  // get element to delete
  ListNode* before = traverse->prev;           // get element before deletion
  ListNode* after = traverse->next;            // get element after deletion

  delete traverse;  // delete element
  // link before and after
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
  int cnt = 0;        // counter for matches
  while (i != -1) {   // while we can find matching values
    erase(i);         // delete them
    i = find(value);  // find the next
    cnt++;            // and keep count
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
  ListNode* traverse = head_;      // walk starting from head
  while (traverse != nullptr) {    // keep walking while elements
    if (traverse->val == value) {  // check for match
      return i;
    }
    traverse = traverse->next;  // walk forward
    i++;
  }
  return -1;
}

Sequence::ListNode* Sequence::get_ptr_to_index(int pos) const {
  if (pos >= size() || pos < 0 || size() == 0) {
    return nullptr;
  }
  ListNode* traverse = head_;       // start walking at head
  for (int i = 1; i <= pos; i++) {  // walk until pos
    traverse = traverse->next;      // walk forward
  }
  return traverse;  // the pointer is what we need
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
