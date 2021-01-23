#include <cassert>
#include <iostream>

#include "newSequence.h"
using namespace std;

int main() {
  Sequence a(1000);  // a can hold at most 1000 items
  Sequence b(5);     // b can hold at most 5 items
  Sequence c;        // c can hold at most DEFAULT_MAX_ITEMS items
  ItemType v = 1;

  // No failures inserting 5 items into b
  for (int k = 0; k < 5; k++) assert(b.insert(v) != -1);

  // Failure if we try to insert a sixth item into b
  assert(b.insert(v) == -1);

  // When two Sequences' contents are swapped, their capacities are
  // swapped as well:
  a.swap(b);

  assert((a.insert(v) == -1) && (b.insert(v) != -1));

  Sequence s(6);
  assert(s.empty());
  assert(s.find(42) == -1);
  assert(s.insert(42) == 0);
  assert(s.insert(32) == 0);
  assert(s.insert(22) == 0);
  assert(s.insert(22) == 0);
  assert(s.insert(22) == 0);
  assert(s.insert(11) == 0);
  assert(s.size() == 6 && s.find(42) == 5);
  assert(s.remove(22) == 3);
  assert(s.size() == 3 && s.find(42 == 2));

  Sequence d(5);
  assert(d.insert(4) == 0);
  assert(d.insert(3) == 0);
  assert(d.insert(2) == 0);
  assert(d.insert(2) == 0);
  assert(d.insert(1) == 0);

  s.swap(d);

  assert(d.size() == 3 && d.find(42) == 2);
  assert(s.size() == 5 && s.find(4) == 4);

  Sequence e;
  for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
    assert(e.insert(DEFAULT_MAX_ITEMS - i) == 0);
  }
  assert(e.insert(0) == -1);
  assert(e.size() == DEFAULT_MAX_ITEMS && e.find(100 == DEFAULT_MAX_ITEMS - 1));

  Sequence f;
  for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
    assert(f.insert(3) == 0);
  }
  assert(f.remove(3) == DEFAULT_MAX_ITEMS);
  assert(f.empty());

  cout << "Passed all tests" << endl;
}
