#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Coord {
 public:
  Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
  int r() const { return m_row; }
  int c() const { return m_col; }

 private:
  int m_row;
  int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er,
                int ec) {
  stack<Coord> coordStack;
  coordStack.push(Coord(sr, sc));  // Push starting coord;
  maze[sr][sc] = 'D';
  while (!coordStack.empty()) {
    Coord top = coordStack.top();
    coordStack.pop();

    // cout << "R: " << top.r() << "\tC: " << top.c() << endl;

    if (top.r() == er && top.c() == ec) {
      return true;
    }
    const int r = top.r();
    const int c = top.c();
    if (maze[r - 1][c] == '.') {
      coordStack.push(Coord(r - 1, c));
      maze[r - 1][c] = 'D';
    }
    if (maze[r][c + 1] == '.') {
      coordStack.push(Coord(r, c + 1));
      maze[r][c + 1] = 'D';
    }
    if (maze[r + 1][c] == '.') {
      coordStack.push(Coord(r + 1, c));
      maze[r + 1][c] = 'D';
    }
    if (maze[r][c - 1] == '.') {
      coordStack.push(Coord(r, c - 1));
      maze[r][c - 1] = 'D';
    }
  }

  return false;
}
