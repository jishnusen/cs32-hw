#include <iostream>
#include <cassert>
using namespace std;

class StringList
{
  public:
    StringList();
    // You may declare other member functions for your test code to call
    void eraseEvens();
  private:
    struct Node
    {
      char  value;
      Node* next;
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList()
{
  head = nullptr;
}

// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseEvens IMPLEMENTATION

void StringList::eraseEvens() {
  int i = 1;
  Node* prev = nullptr;
  Node* traverse = head;
  while (traverse != nullptr) {
    if (i % 2 == 0) {
      prev->next = traverse->next;
      delete traverse;
    }
    prev = traverse;
    traverse = traverse->next;
    i++;
  }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseEvens IMPLEMENTATION

int main()
{
  // You may put some code here for test purposes
  cout << "All tests succeeded" << endl;
}
