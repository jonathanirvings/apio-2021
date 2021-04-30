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

  std::vector<std::vector<int>> dp(N, std::vector<int>(N)), opt = dp;
  for (int r = 0; r < N; ++r) {
    opt[r][r] = r;
    dp[r][r] = 0;
    for (int l = r - 1; l >= 0; --l) {
      dp[l][r] = -1;
      for (int k = opt[l][r - 1]; k <= std::min(opt[l + 1][r], r - 1); ++k) {
        int res = dp[l][k] + dp[k + 1][r] + 
                  (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
                  (lft[k + 1][r] - lft[l][r] + rgt[l][r] - rgt[k + 1][r]);
        if (dp[l][r] == -1 || res < dp[l][r]) {
          dp[l][r] = res;
          opt[l][r] = k;
        }
      }
    }
  }

  return dp[0][N - 1] + lft[0][N - 1] + M - rgt[0][N - 1];
}
