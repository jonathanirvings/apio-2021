#include "boxes.h"

#include <bits/stdc++.h>

int minimum_lifts(int N, int M, std::vector<int> A) {
  std::vector<std::vector<int>> lft(N, std::vector<int>(N)), rgt = lft;
  for (int i = 0; i < N; ++i) {
    lft[i][i] = rgt[i][i] = A[i];
    for (int j = i + 1; j < N; ++j) {
      lft[i][j] = std::min(lft[i][j - 1], A[j]);
      rgt[i][j] = std::max(rgt[i][j - 1], A[j]);
    }
  }

  std::function<int(int, int)> dfs = [&](int l, int r) {
    if (l == r) return 0;
    for (int k = r - 1; k >= l; --k) {
      if (lft[l][k] == lft[l][r] && rgt[l][k] == rgt[l][r]) continue;
      return dfs(l, k) + dfs(k + 1, r) + 
             (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
             (lft[k + 1][r] - lft[l][r] + rgt[l][r] - rgt[k + 1][r]);
    }
    return 0;
  };

  return dfs(0, N - 1) + lft[0][N - 1] + M - rgt[0][N - 1];
}
