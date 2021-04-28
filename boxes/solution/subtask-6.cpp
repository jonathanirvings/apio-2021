#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e3;
const int INF=1e9;

int L[MAXN][MAXN];
int R[MAXN][MAXN];
int dp[MAXN][MAXN];
int cost;

int minimum_lifts(int N, int M, vector<int> A) {
  for (int i=0;i<N;i++) {
    L[i][i]=R[i][i]=A[i];
    if (!i) continue;
    dp[i-1][i]=2*((R[i-1][i]=max(A[i-1],A[i]))-(L[i-1][i]=min(A[i-1],A[i])));
    for (int j=i-1;j--;) {
      L[j][i]=min(L[j][i-1],A[i]);
      R[j][i]=max(R[j][i-1],A[i]);
      dp[j][i]=INF;
      for (int k=j;k<i;k++) {
        dp[j][i]=min(dp[j][i],dp[j][k]+dp[k+1][i]+abs(L[j][k]-L[k+1][i])+abs(R[j][k]-R[k+1][i]));
      }
    }
  }
  return dp[0][N-1]+L[0][N-1]-R[0][N-1]+M;
}
