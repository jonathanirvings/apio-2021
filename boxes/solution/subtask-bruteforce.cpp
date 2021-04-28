#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int dist;
vector <int> loc;

int solve(int L,int R,int X,int Y) {
  if (L > R || X+Y == dist) {
    return 0;
  }
  int ret=INF, x=dist, y=dist;
  for (int i = L; i <= R; i++) {
    x = min(x, loc[i]);
    y = min(y, dist-loc[i]);
    if (x == X && y == Y) break;
    ret = min(ret, x-X+y-Y+solve(i+1,R,X,Y)+solve(L,i,x,y));
  }
  return ret;
}

int minimum_lifts(int N, int M, vector<int> A) {
  dist = M;
  loc = A;
  return solve(0,N-1,0,0);
}
