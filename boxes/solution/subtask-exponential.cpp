#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXB = 1<<MAXN;
const int INF = 1e9;

struct boxes {
  int cost, x, y;
  
  void build(int xpos,int ypos) {
    cost = 0;
    x = xpos;
    y = ypos;
  }
  
  void merge(boxes A,boxes B) {
    x = min(A.x,B.x);
    y = min(A.y,B.y);
    cost = min(cost,A.cost+B.cost+abs(A.x-B.x)+abs(A.y-B.y));
  }
  
  int ans() {
    return cost+x+y;
  }
}
dp[MAXB];

int minimum_lifts(int N, int M, vector<int> A) {
  for (int i=1; i < (1<<N); i++) {
    dp[i].cost = INF;
    for (int j=0, k=0; j < N; j++) {
      if (i == (1<<j)) {
        dp[i].build(A[j], M-A[j]);
        break;
      }
      if ((i>>j)&1) {
        k += 1<<j;
      }
      if (k != i) {
        dp[i].merge(dp[k], dp[i^k]);
      }
    }
  }
  return dp[(1<<N)-1].ans();
}
