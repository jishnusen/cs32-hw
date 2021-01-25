#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <string>

using ItemType = unsigned long;

class Sequence {
 public:
  Sequence();
  Sequence(const Sequence& obj);
  ~Sequence();

  Sequence& operator=(const Sequence& obj);
  bool empty() const;
  int size() const;
  int insert(int pos, const ItemType& value);
  int insert(const ItemType& value);
  bool erase(int pos);
  int remove(const ItemType& value);
  bool get(int pos, ItemType& value) const;
  bool set(int pos, const ItemType& value);
  int find(const ItemType& value) const;
  void swap(Sequence& other);
  void dump() const;

 private:
  struct ListNode {
    ListNode* prev = nullptr;  // Pointer to previous element of list
    ListNode* next = nullptr;  // Pointer to next element of list
    ItemType val;              // Stored value in list element
  };
  void deleteList();
  ListNode* get_ptr_to_index(int pos) const;
  ListNode* head_;  // Pointer to start of doubly-linked list
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif  // SEQUENCE_H_