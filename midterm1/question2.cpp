#include <iostream>
#include <cassert>
using namespace std;

class Num
{
  public:
    Num(int i) : m_i(i) {}
    int geti() const { return m_i; }
  private:
    int m_i;
};

class Blah
{
  public:
    Blah(int i);
    ~Blah();
    Blah(const Blah& other);
  private:
    Num* m_num;
    int m_ii;
    int* m_eyes;
};
  
Blah::Blah(int i)
{
  m_num = new Num(i);
  m_ii = 2 * i;
  m_eyes = &m_ii;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

Blah::~Blah() {
  delete m_num;
}

Blah::Blah(const Blah& other) {
  m_num = new Num(*other.m_num);
  m_ii = other.m_ii;
  int tmp_eyes = *other.m_eyes;
  m_eyes = &tmp_eyes;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

void test()
{
  Blah b1(3);
  Blah b2(b1);
}

int main()
{
  test();
  cout << "All tests succeeded" << endl;
}
