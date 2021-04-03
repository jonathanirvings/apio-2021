#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxN = 100000;
constexpr int kMaxQ = 100000;
constexpr int kMaxA = 1000000000;
constexpr int kMaxX = 1000000000;

struct Test {
  vector<int> A, B, X, Y;

  void print() {
    int N = A.size();
    int Q = X.size();
    printf("%d %d\n", N, Q);
    for (int i = 0; i < N; ++i) {
      printf("%d%c", A[i], " \n"[i == N - 1]);
    }
    for (int i = 0; i < N; ++i) {
      printf("%d%c", B[i], " \n"[i == N - 1]);
    }
    for (int i = 0; i < Q; ++i) {
      printf("%d %d\n", X[i], Y[i]);
    }
  }
};

Test randomCase(int N, int Q, int min_elem, int max_elem,
                bool X_equals_one, bool Y_equals_one) {
  Test T;
  unordered_map<int, int> counter;
  for (int i = 0; i < N; ++i) {
    T.A.push_back(rnd.next(min_elem, max_elem));
    T.B.push_back(rnd.next(i + 1, min(N, i + 10)));
    ++counter[T.A[i]];
  }
  for (int i = 0; i < Q; ++i) {
    T.X.push_back(rnd.next(min_elem, min(kMaxX, max_elem + 1)));
    T.Y.push_back(rnd.next(1, min(N, counter[T.X[i]] + 1)));
    if (X_equals_one) {
      T.X[i] = 1;
    }
    if (Y_equals_one) {
      T.Y[i] = 1;
    }
  }
  return T;
}

Test sqrtCase(int N, int Q) {
  Test T;
  int M = (int)floor(sqrt(N));
  for (int i = 0; i < N; ++i) {
    T.A.push_back(i % M + 1);
    T.B.push_back(i + 1);
  }
  for (int i = 0; i < Q; ++i) {
    T.X.push_back(i / M + 1);
    T.Y.push_back(i % M + 1);
  }
  return T;
}

// Kills solutions that do not "jumps" the Xs.
Test mustJumpCase(int N, int Q, int min_elem, int max_elem) {
  Test T;
  int C = rnd.next(min_elem, max_elem);
  for (int i = 0; i < N; ++i) {
    T.A.push_back(C);
    T.B.push_back(i + 1);
  }
  for (int i = 0; i < Q; ++i) {
    T.X.push_back(C);
    T.Y.push_back(i + 1);
  }
  return T;
}

// Kills solutions that do not use binary search to "jumps" the Ys.
Test mustUseBinarySearchCase(int N, int Q, int min_elem, int max_elem) {
  Test T;
  int C = rnd.next(min_elem, max_elem);
  for (int i = 0; i < N; ++i) {
    T.A.push_back(C);
    T.B.push_back(N);
  }
  for (int i = 0; i < Q; ++i) {
    T.X.push_back(C);
    T.Y.push_back(i + 1);
  }
  return T;
}

// Kills solutions that do not memoize answers.
Test mustMemoizeAnswerCase(int N, int Q, int min_elem, int max_elem) {
  Test T;
  int C = rnd.next(min_elem, max_elem);
  for (int i = 0; i < N; ++i) {
    T.A.push_back(C);
    T.B.push_back(i + 1);
  }
  for (int i = 0; i < Q; ++i) {
    T.X.push_back(C);
    T.Y.push_back(1);
  }
  return T;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 0);
  
  if (strcmp(argv[1], "random") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int min_elem = atoi(argv[6]);
    int max_elem = atoi(argv[7]);
    int X_equals_one = atoi(argv[8]);
    int Y_equals_one = atoi(argv[9]);
    randomCase(N, Q, min_elem, max_elem, X_equals_one, Y_equals_one).print();
  } else if (strcmp(argv[1], "sqrt") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    sqrtCase(N, Q).print();
  } else if (strcmp(argv[1], "must-jump") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int min_elem = atoi(argv[6]);
    int max_elem = atoi(argv[7]);
    mustJumpCase(N, Q, min_elem, max_elem).print();
  } else if (strcmp(argv[1], "must-use-binary-search") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int min_elem = atoi(argv[6]);
    int max_elem = atoi(argv[7]);
    mustUseBinarySearchCase(N, Q, min_elem, max_elem).print();
  } else if (strcmp(argv[1], "must-memoize-answer") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int min_elem = atoi(argv[6]);
    int max_elem = atoi(argv[7]);
    mustMemoizeAnswerCase(N, Q, min_elem, max_elem).print();
  }
}
