#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Test {
  int N;
  vector<int> L, R, H;

  Test(int _N): N(_N) {}

  void print() {
    int Q = L.size();
    printf("%d %d\n", N, Q);
    for (int i = 0; i < Q; ++i) {
      printf("%d %d %d\n", L[i], R[i], H[i]);
    }
  }

  void addQuery(int l, int r, int h) {
    L.push_back(l);
    R.push_back(r);
    H.push_back(h);
  }
};

struct RMQ {
  vector<vector<int>> maxi;

  RMQ(const vector<int> &H) {
    maxi.push_back(H);
    int N = H.size();
    for (int i = 1; 1 << i < N; ++i) {
      maxi.push_back(vector<int>());
      for (int j = 0; j + (1 << i) <= N; ++j) {
        maxi[i].push_back(max(maxi[i - 1][j], maxi[i - 1][j + (1 << (i - 1))]));
      }
    }
  }

  int query(int l, int r) {
    if (l == r) return maxi[0][l];
    int lg = 31 - __builtin_clz(r - l);
    return max(maxi[lg][l], maxi[lg][r - (1 << lg) + 1]);
  }
};

vector<int> randomArray(int N, int max_H) {
  vector<int> ret(N);
  for (int i = 0; i < N; ++i) {
    ret[i] = rnd.next(1, max_H);
  }
  return ret;
}

vector<int> randomSorted(int N, int max_H) {
  vector<int> ret = randomArray(N, max_H);
  sort(ret.begin(), ret.end());
  return ret;
}

vector<int> randomSortedDistinct(int N, int max_H) {
  assert(N <= max_H);
  if (N * 2 < max_H) {
    set<int> elements;
    while (static_cast<int>(elements.size()) < N) {
      elements.insert(rnd.next(1, max_H));
    }
    vector<int> ret(elements.begin(), elements.end());
    return ret;
  }
  vector<int> ret(max_H);
  iota(ret.begin(), ret.end(), 1);
  shuffle(ret.begin(), ret.end());
  ret.resize(N);
  sort(ret.begin(), ret.end());
  return ret;
}

Test randomCase(int N, int Q, int max_H) {
  Test T(N);

  for (int i = 0; i < Q; ++i) {
    int l = rnd.next(N), r = rnd.next(N);
    if (l > r) swap(l, r);
    T.addQuery(l, r, rnd.next(1, max_H));
  }

  return T;
}

Test randomConsistentCase(int N, int Q, int max_H) {
  Test T(N);

  RMQ rmq(randomArray(N, max_H));
  for (int i = 0; i < Q; ++i) {
    int l = rnd.next(N), r = rnd.next(N);
    if (l > r) swap(l, r);
    T.addQuery(l, r, rmq.query(l, r));
  }

  return T;
}

Test randomAlmostConsistentCase(int N, int Q, int max_H) {
  Test T(N);

  vector<int> H = randomArray(N, max_H);
  RMQ rmq(H);
  for (int i = 0; i < Q / 2; ++i) {
    int l = rnd.next(N), r = rnd.next(N);
    if (l > r) swap(l, r);
    T.addQuery(l, r, rmq.query(l, r));
  }

  for (int i = 0; i < N / 4; ++i) {
    ++(H[rnd.next(N)] %= max_H);
  }
  rmq = RMQ(H);
  for (int i = Q / 2; i < Q; ++i) {
    int l = rnd.next(N), r = rnd.next(N);
    if (l > r) swap(l, r);
    T.addQuery(l, r, rmq.query(l, r));
  }

  return T;
}

Test queryAllThenEach(int N, int max_H) {
  Test T(N);
  vector<int> H = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  int maxi = *max_element(H.begin(), H.end());
  T.addQuery(0, N - 1, maxi);
  for (int i = 0; i < N; ++i) {
    T.addQuery(i, i, H[i]);
  }
  T.addQuery(0, N - 1, maxi - 1);
  return T;
}

Test shrinkingQueries(int N, int max_H) {
  Test T(N);
  vector<int> elements = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  for (int l = 0, r = N - 1; l <= r; rnd.next(2) ? ++l : --r) {
    T.addQuery(l, r, elements[r - l]);
  }
  T.addQuery(0, N - 1, elements.back() - 1);
  return T;
}

Test doublyShrinkingQueries(int N, int max_H) {
  Test T(N);
  vector<int> elements = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  for (int l = 0, r = N - 1; l < N; ++l, --r) {
    if (r - l <= 1) r = N - 1;
    T.addQuery(l, r, elements[N - l - 1]);
  }
  T.addQuery(0, N - 1, elements.back() - 1);
  return T;
}

Test quickSortQueries(int N, int max_H) {
  Test T(N);
  vector<int> elements = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  function<void(int, int)> dfs = [&dfs, &T, &elements](int l, int r) {
    if (l > r) return;
    int mid = rnd.next(l, r);
    T.addQuery(l, r, elements.back());
    elements.pop_back();

    if (rnd.next(2)) {
      dfs(l, mid - 1);
      dfs(mid + 1, r);
    } else {
      dfs(mid + 1, r);
      dfs(l, mid - 1);
    }
  };
  dfs(0, N - 1);
  return T;
}

Test randomPointQueries(int N, int Q, int max_H) {
  Test T(N);
  for (int i = 0; i < Q; ++i) {
    int x = rnd.next(N);
    T.addQuery(x, x, rnd.next(1, max_H));
  }
  return T;
}

Test randomConsistentPointQueriesExceptLast(int N, int Q, int max_H) {
  Test T(N);
  vector<int> H = randomArray(N, max_H);
  for (int i = 0; i < Q - 1; ++i) {
    int x = rnd.next(N);
    T.addQuery(x, x, H[x]);
  }
  int firstPoint = T.L[0];
  ++(H[firstPoint] %= max_H);
  T.addQuery(firstPoint, firstPoint, H[firstPoint]);
  return T;
}

Test randomConstantDifference(int N, int Q, int max_H, int difference) {
  Test T(N);
  for (int i = 0; i < Q; ++i) {
    int l = rnd.next(N - difference + 1);
    T.addQuery(l, l + difference - 1, rnd.next(1, max_H));
  }
  return T;
}

Test randomAlmostConsistentConstantDifference(int N, int Q, int max_H, int difference) {
  Test T(N);

  vector<int> H = randomArray(N, max_H);
  RMQ rmq(H);
  for (int i = 0; i < Q / 2; ++i) {
    int l = rnd.next(N - difference + 1);
    int r = l + difference - 1;
    T.addQuery(l, r, rmq.query(l, r));
  }

  for (int i = 0; i < N / 4; ++i) {
    ++(H[rnd.next(N)] %= max_H);
  }
  rmq = RMQ(H);
  for (int i = Q / 2; i < Q; ++i) {
    int l = rnd.next(N - difference + 1);
    int r = l + difference - 1;
    T.addQuery(l, r, rmq.query(l, r));
  }

  return T;
}

Test orderedConstantDifference(int N, int max_H, int difference) {
  Test T(N);
  vector<int> H = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  for (int i = N - difference; i >= 0; --i) {
    T.addQuery(i, i + difference - 1, H[i + difference - 1]);
  }
  T.addQuery(N - difference, N - 1, H.back() % max_H + 1);
  return T;
}

Test randomLZero(int N, int Q, int max_H) {
  Test T(N);
  for (int i = 0; i < Q; ++i) {
    T.addQuery(0, rnd.next(N), rnd.next(1, max_H));
  }
  return T;
}

Test randomConsistentLZeroExceptLast(int N, int max_H) {
  Test T(N);
  vector<int> H = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  vector<int> permutation = randomSortedDistinct(N, N);
  shuffle(permutation.begin(), permutation.end());
  for (int i = 0; i < N; ++i) {
    T.addQuery(0, permutation[i] - 1, H[permutation[i] - 1]);
  }
  T.addQuery(0, 0, H[0] % max_H + 1);
  return T;
}

Test orderedLZero(int N, int max_H) {
  Test T(N);
  vector<int> H = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  for (int i = N - 1; i >= 0; --i) {
    T.addQuery(0, i, H[i]);
  }
  T.addQuery(0, 0, H[0] % max_H + 1);
  return T;
}

Test pointsThenShrinkingQueries(int N, int max_H) {
  Test T(N);
  vector<int> H = max_H >= N ? randomSortedDistinct(N, max_H) : randomSorted(N, max_H);
  for (int i = 1; i < N; i += 2) {
    T.addQuery(i, i, H[i / 2]);
  }
  for (int i = 0, l = 0, r = N - 1; l <= r; ++i & 1 ? l += 2 : r -= 2) {
    T.addQuery(l, r, H[N - i - 1]);
  }
  T.addQuery(0, N - 1, H[N - 1] % max_H + 1);
  return T;
}

Test counterWrongSampling(int _N) {
  Test T(_N);

  int N = _N * 9 / 10;
  N -= N % 3;

  // noises
  vector<int> H = randomArray(_N - N, 5);
  for (int i = 0; i < N / 3; ++i) {
    int l = rnd.next(N + 1, _N - 1);
    int r = min(l + rnd.next(10), _N - 1);
    T.addQuery(l, r, *max_element(H.begin() + l - (N + 1), H.begin() + r - N));
  }

  int width = N / 3;
  int t1 = width, t2 = width * 2;
  for (int i = 0; i < t1 - 2; ++i) {
    T.addQuery(i, t2, 5);
  }
  for (int i = N - 1; i > t2 + 2; --i) {
    T.addQuery(t1, i, 5);
  }
  for (int i = 0; i + width < N; ++i) {
    T.addQuery(i, i + width, 5);
  }

  int mid = N / 2;

  T.addQuery(0, t1 - 2, 3);
  T.addQuery(t1, mid - 1, 3);
  T.addQuery(mid + 1, t2, 3);
  T.addQuery(t2 + 2, N, 3);
  T.addQuery(mid - 2, mid + 2, 3);

  return T;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 0);
  
  if (strcmp(argv[1], "random") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomCase(N, Q, max_H).print();
  } else if (strcmp(argv[1], "random_consistent") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomConsistentCase(N, Q, max_H).print();
  } else if (strcmp(argv[1], "random_almost_consistent") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomAlmostConsistentCase(N, Q, max_H).print();
  } else if (strcmp(argv[1], "query_all_then_each") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    queryAllThenEach(N, max_H).print();
  } else if (strcmp(argv[1], "shrinking_queries") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    shrinkingQueries(N, max_H).print();
  } else if (strcmp(argv[1], "doubly_shrinking_queries") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    doublyShrinkingQueries(N, max_H).print();
  } else if (strcmp(argv[1], "quick_sort_queries") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    quickSortQueries(N, max_H).print();
  } else if (strcmp(argv[1], "random_point_queries") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomPointQueries(N, Q, max_H).print();
  } else if (strcmp(argv[1], "random_consistent_point_queries_except_last") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomConsistentPointQueriesExceptLast(N, Q, max_H).print();
  } else if (strcmp(argv[1], "random_constant_difference") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    int difference = atoi(argv[7]);
    randomConstantDifference(N, Q, max_H, difference).print();
  } else if (strcmp(argv[1], "random_almost_consistent_constant_difference") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    int difference = atoi(argv[7]);
    randomAlmostConsistentConstantDifference(N, Q, max_H, difference).print();
  } else if (strcmp(argv[1], "ordered_constant_difference") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    int difference = atoi(argv[5]);
    orderedConstantDifference(N, max_H, difference).print();
  } else if (strcmp(argv[1], "random_l_zero") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int Q = rnd.next(atoi(argv[4]), atoi(argv[5]));
    int max_H = atoi(argv[6]);
    randomLZero(N, Q, max_H).print();
  } else if (strcmp(argv[1], "random_consistent_l_zero_except_last") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    randomConsistentLZeroExceptLast(N, max_H).print();
  } else if (strcmp(argv[1], "ordered_l_zero") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    orderedLZero(N, max_H).print();
  } else if (strcmp(argv[1], "points_then_shrinking_queries") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    int max_H = atoi(argv[4]);
    pointsThenShrinkingQueries(N, max_H).print();
  } else if (strcmp(argv[1], "counter_wrong_sampling") == 0) {
    int N = rnd.next(atoi(argv[2]), atoi(argv[3]));
    counterWrongSampling(N).print();
  } else {
    assert(0);
  }
  return 0;
}
