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
