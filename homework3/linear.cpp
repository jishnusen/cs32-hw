#include <cassert>
#include <iostream>
using namespace std;

bool somePredicate(double x) { return x < 0; }

bool anyTrue(const double a[], int n) {
  if (n <= 0) {
    return false;
  } else if (somePredicate(a[n - 1])) {
    return true;
  } else {
    return anyTrue(a, n - 1);
  }
}

int countTrue(const double a[], int n) {
  if (n <= 0) {
    return 0;
  } else if (somePredicate(a[n - 1])) {
    return 1 + countTrue(a, n - 1);
  } else {
    return countTrue(a, n - 1);
  }
}

int firstTrue(const double a[], int n) {
  if (n <= 0) {
    return -1;
  } else if (somePredicate(a[n - 1]) && n > 1) {
    int f = firstTrue(a, n - 1);
    if (f == -1) {
      return n - 1;
    } else {
      return min(f, n - 1);
    }
  } else {
    return firstTrue(a, n - 1);
  }
}

int positionOfMax(const double a[], int n) {
  if (n <= 0) {
    return -1;
  } else if (a[n - 1] >= positionOfMax(a, n - 1)) {
    return n - 1;
  } else {
    return positionOfMax(a, n - 1);
  }
}

bool isIn(const double a1[], int n1, const double a2[], int n2) {
  if (n1 <= 0) {
    return true;
  } else if (n2 <= 0) {
    return false;
  } else if (a1[n1 - 1] == a2[n2 - 1]) {
    return isIn(a1, n1 - 1, a2, n2 - 1);
  } else {
    return isIn(a1, n1, a2, n2 - 1);
  }
}

int main() {
  double a[4] = {-1, 1, 2, 3};
  double b[4] = {1, -1, 2, 3};
  double c[4] = {1, 1, 2, -3};
  assert(anyTrue(a, 4));
  assert(anyTrue(b, 4));
  assert(anyTrue(c, 4));
  double d[4] = {1, 1, -2, -3};
  assert(countTrue(a, 4) == 1);
  assert(countTrue(b, 4) == 1);
  assert(countTrue(c, 4) == 1);
  assert(countTrue(d, 4) == 2);

  assert(positionOfMax(a, 4) == 3);
  assert(positionOfMax(c, 4) == 2);
  assert(positionOfMax(a, 0) == -1);

  assert(firstTrue(d, 4) == 2);
  assert(firstTrue(d, 0) == -1);

  double a2[7] =  {10, 50, 40, 20, 50, 40, 30};
  double a1[3] = {50, 20, 30};

  assert(isIn(a1, 3, a2, 7));
  a1[1] = 40;
  a1[2] = 40; // 50 40 40
  assert(isIn(a1, 3, a2, 7));
  a1[1] = 30;
  a1[2] = 20; // 50 30 20
  assert(!isIn(a1, 3, a2, 7));
  a1[0] = 10;
  a1[1] = 20; // 10 20 20
  assert(!isIn(a1, 3, a2, 7));
}
