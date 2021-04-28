#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e3;

int dp[MAXN];

int minimum_lifts(int N, int, vector<int>) {
  for (int i = 2; i <= N; i++) {
    dp[i] = dp[i/2]+dp[i-i/2]+i;
  }
  return dp[N];
}
