#include <cassert>
#include <iostream>

#include "Sequence.h"
using namespace std;

int main() {
  Sequence s;
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

  Sequence a;
  assert(a.insert(4) == 0);
  assert(a.insert(3) == 0);
  assert(a.insert(2) == 0);
  assert(a.insert(2) == 0);
  assert(a.insert(1) == 0);

  s.swap(a);

  assert(a.size() == 3 && a.find(42) == 2);
  assert(s.size() == 5 && s.find(4) == 4);

  Sequence b;
  for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
    assert(b.insert(DEFAULT_MAX_ITEMS - i) == 0);
  }
  assert(b.insert(0) == -1);
  assert(b.size() == DEFAULT_MAX_ITEMS && b.find(100 == DEFAULT_MAX_ITEMS - 1));

  Sequence c;
  for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
    assert(c.insert(3) == 0);
  }
  assert(c.remove(3) == DEFAULT_MAX_ITEMS);
  assert(c.empty());

  cout << "Passed all tests" << endl;
}
