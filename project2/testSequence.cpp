#include <cassert>
#include <iostream>

#include "Sequence.h"
using namespace std;

int main() {
  Sequence t;
  t.insert(0, 1);
  t.insert(0, 2);
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
  s.dump();

  s.swap(a);

  a.dump();
  assert(a.size() == 3 && a.find(42) == 2);
  assert(s.size() == 5 && s.find(4) == 4);

  cout << "Passed all tests" << endl;
}
