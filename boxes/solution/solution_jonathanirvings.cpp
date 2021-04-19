#include "boxes.h"

#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> position;
vector<vector<int>> dp;

int group(int a, int b, int c) {
  return abs(position[a][b].first - position[b + 1][c].first)
       + abs(position[a][b].second - position[b + 1][c].second);
}

void dnc(int L, int R, int optL, int optR, int dif) {
  if (L > R) {
    return;
  }

  int M = (L + R) >> 1;
  int opt = -1;
  int &ret = dp[M][M + dif];
  ret = INT_MAX;
  for (int i = max(M, optL); i <= min(M + dif - 1, optR); ++i) {
    int res = dp[M][i] + dp[i + 1][M + dif] + group(M, i, M + dif);
    if (res < ret) {
      ret = res;
      opt = i;
    }
  }
  assert(opt >= 0);
  dnc(L, M - 1, optL, opt, dif);
  dnc(M + 1, R, opt, optR, dif);
}

int minimum_lifts(int N, int M, vector<int> A) {
  dp = vector<vector<int>>(N, vector<int>(N, 0));
  position = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(N));
  for (int i = 0; i < N; ++i) {
    position[i][i] = make_pair(A[i], M - A[i]);
    for (int j = i + 1; j < N; ++j) {
      position[i][j] = position[i][j - 1];
      position[i][j].first = min(position[i][j].first, A[j]);
      position[i][j].second = min(position[i][j].second, M - A[j]);
    }
  }
  for (int dif = 1; dif < N; ++dif) {
    dnc(0, N - dif - 1, 0, N - 1, dif);
  }
  return dp[0][N - 1] + position[0][N - 1].first + position[0][N - 1].second;
}
