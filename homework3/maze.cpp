/* #include <iostream> */
/* #include <queue> */
/* #include <string> */

/* using namespace std; */

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
  if (sr == er && sc == ec) {
    return true;
  }
  maze[sr][sc] = 'D';
  for (int i = 0; i < 4; i++) {
    bool negative = i & 1;
    bool row = i >> 1;
    int r = sr;
    int c = sc;
    if (row) {
      r += 1 * (negative ? -1 : 1);
    } else {
      c += 1 * (negative ? -1 : 1);
    }
    if (maze[r][c] == '.' && pathExists(maze, nRows, nCols, r, c, er, ec)) {
      return true;
    }
  }
  return false;
}

/* int main() { */
/*   string maze[10] = {"XXXXXXXXXX", "X........X", "XX.X.XXXXX", "X..X.X...X", */
/*                      "X..X...X.X", "XXXX.XXX.X", "X.X....XXX", "X..XX.XX.X", */
/*                      "X...X....X", "XXXXXXXXXX"}; */

/*   if (pathExists(maze, 10, 10, 6, 4, 1, 1)) */
/*     cout << "Solvable!" << endl; */
/*   else */
/*     cout << "Out of luck!" << endl; */
/* } */
