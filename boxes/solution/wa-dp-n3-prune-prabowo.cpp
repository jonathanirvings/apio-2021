#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include "boxes.h"

#include <vector>

const int kMaxN = 2000;
const int kInf = 2e9;
const int kMagic = 40;

int lft[kMaxN][kMaxN];
int rgt[kMaxN][kMaxN];
int dp[kMaxN][kMaxN];

int minimum_lifts(int N, int M, std::vector<int> A) {
  for (int i = 0; i < N; ++i) {
    lft[i][i] = rgt[i][i] = A[i];
    for (int j = i + 1; j < N; ++j) {
      lft[i][j] = lft[i][j - 1] < A[j] ? lft[i][j - 1] : A[j];
      rgt[i][j] = rgt[i][j - 1] > A[j] ? rgt[i][j - 1] : A[j];
    }
    for (int j = i - 1; j >= 0; --j) {
      lft[i][j] = lft[i][j + 1] < A[j] ? lft[i][j + 1] : A[j];
      rgt[i][j] = rgt[i][j + 1] > A[j] ? rgt[i][j + 1] : A[j];
    }
  }

  for (int l = N - 1; l >= 0; --l) {
    dp[l][l] = 0;
    for (int r = l + 1; r < N; ++r) {
      dp[l][r] = kInf;
      if (r - l < kMagic * 2) {
        for (int k = l; k < r; ++k) {
          int res = dp[l][k] + dp[r][k + 1] + 
                    (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
                    (lft[r][k + 1] - lft[l][r] + rgt[l][r] - rgt[r][k + 1]);
          if (res < dp[l][r]) dp[l][r] = res;
        }
      } else {
        for (int k = l; k < l + kMagic; ++k) {
          int res = dp[l][k] + dp[r][k + 1] + 
                    (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
                    (lft[r][k + 1] - lft[l][r] + rgt[l][r] - rgt[r][k + 1]);
          if (res < dp[l][r]) dp[l][r] = res;
        }

        int midL = (r + l - kMagic) >> 1;
        int midR = (r + l + kMagic) >> 1;
        if (midL < l + kMagic) midL = l + kMagic;
        if (midR > r - kMagic) midR = r - kMagic;
        for (int k = midL; k < midR; ++k) {
          int res = dp[l][k] + dp[r][k + 1] + 
                    (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
                    (lft[r][k + 1] - lft[l][r] + rgt[l][r] - rgt[r][k + 1]);
          if (res < dp[l][r]) dp[l][r] = res;
        }

        for (int k = r - kMagic; k < r; ++k) {
          int res = dp[l][k] + dp[r][k + 1] + 
                    (lft[l][k] - lft[l][r] + rgt[l][r] - rgt[l][k]) +
                    (lft[r][k + 1] - lft[l][r] + rgt[l][r] - rgt[r][k + 1]);
          if (res < dp[l][r]) dp[l][r] = res;
        }
      }
      dp[r][l] = dp[l][r];
    }
  }

  return dp[0][N - 1] + lft[0][N - 1] + M - rgt[0][N - 1];
}
