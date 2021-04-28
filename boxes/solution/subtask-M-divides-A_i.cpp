#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

int minimum_lifts(int N, int M, vector<int> A) {
  int cnt = 1;
  for (int i = 1; i < N; i++) {
    if (A[i] != A[i-1]) {
      cnt++;
    }
  }
  return M*cnt;
}
