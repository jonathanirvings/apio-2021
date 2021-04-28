#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
const int INF = 1e9;

int dist;
vector <int> loc;
int dp[MAXN][MAXN][MAXN][MAXN];

int solve(int L,int R,int X,int Y) {
  for (int i = L; i <= R; i++) {
    if (X > loc[i] || Y > dist-loc[i]) {
      return INF;
    }
  }
  if (L > R || X+Y == dist) {
    return 0;
  }
  if (dp[L][R][X][Y]) {
    return dp[L][R][X][Y];
  }
  int ret = INF;
  for (int i = L; i <= R; i++) {
    ret = min(ret, 1+solve(i+1,R,X,Y)+solve(L,i,X,Y+1));
    ret = min(ret, 1+solve(i+1,R,X,Y)+solve(L,i,X+1,Y));
  }
  return dp[L][R][X][Y] = ret;
}

int minimum_lifts(int N, int M, vector<int> A) {
  dist = M;
  loc = A;
  return solve(0,N-1,0,0);
}
