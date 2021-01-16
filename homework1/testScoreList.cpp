#include <cassert>
#include <iostream>

#include "ScoreList.h"
using namespace std;

int main() {
  ScoreList score_list;
  for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
    assert(score_list.add(i) ^ (i > 100));
  }

  assert(score_list.size() == 101);
  assert(score_list.maximum() == 100);
  assert(score_list.remove(100));
  assert(score_list.maximum() == 99);
  assert(score_list.size() == 100);
  assert(score_list.add(99));
  assert(score_list.remove(99));
  assert(score_list.size() == 100);
  assert(score_list.minimum() == 0);

  cout << "Passed all tests" << endl;
}