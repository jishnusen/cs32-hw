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
  assert(a.insert(2) == 0);
  assert(a.insert(2) == 0);
  assert(a.insert(1) == 0);
  assert(a.insert(3) == 3);

  s.swap(a);

  assert(a.size() == 3 && a.find(42) == 2);
  assert(s.size() == 5 && s.find(4) == 4);

  Sequence c;
  Sequence d;

  for (int i = 0; i < 10; i++) {
    c.insert(c.size(), i);
  }

  for (int i = 5; i < 10; i++) {
    d.insert(d.size(), i);
  }
  assert(subsequence(c, d) == 5);

  Sequence e;
  for (int i = 5; i < 15; i++) {
    e.insert(e.size(), i);
  }
  assert(subsequence(c, e) == -1);
  assert(subsequence(c, c) == 0);

  Sequence f;
  f.insert(0, 9);
  assert(subsequence(c, f) == 9);

  Sequence r;
  interleave(c, e, r);
  assert(r.size() == 2 * e.size());
  for (int i = 0; i < e.size(); i++) {
    ItemType dummy;

    e.get(i, dummy);
    assert(r.find(dummy) == (i * 2) + 1);
  }

  interleave(a, e, r);
  assert(r.size() == a.size() + e.size());
  for (int i = 0; i < a.size(); i++) {
    ItemType dummy;

    a.get(i, dummy);
    assert(r.find(dummy) == (i * 2));
  }

  interleave(e, a, r);
  assert(r.size() == a.size() + e.size());
  for (int i = 0; i < a.size(); i++) {
    ItemType dummy;

    a.get(i, dummy);
    assert(r.find(dummy) == (i * 2) + 1);
  }

  Sequence empty;
  interleave(empty, empty, r);
  assert(r.size() == 0);

  interleave(a, empty, r);
  assert(r.size() == a.size());

  interleave(empty, a, r);
  assert(r.size() == a.size());

  empty.swap(a);
  assert(empty.size() == 3);
  assert(a.size() == 0);
  a.swap(empty);
  assert(empty.size() == 0);
  assert(a.size() == 3);

  interleave(a, a, a);  // Result: [11, 11, 32, 32, 42, 42]
  assert(a.size() == 6);
  assert(a.find(32) == 2);

  cout << "Passed all tests" << endl;
}

/*#include "Sequence.h"
#include <cassert>
#include <iostream>
using namespace std;

void test() {
  Sequence s;
  assert(s.insert(0, 10) == 0);
  assert(s.insert(0, 20) == 0);
  assert(s.size() == 2);
  ItemType x = 999;
  assert(s.get(0, x) && x == 20);
  assert(s.get(1, x) && x == 10);
}

int main() {
  test();
  cout << "Passed all tests" << endl;
}*/