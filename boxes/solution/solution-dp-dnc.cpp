#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e3;
const int INF=1e9;

int L[MAXN][MAXN];
int R[MAXN][MAXN];
int dp[MAXN][MAXN];
int cost,fin,val,opt;

void dnc(int idl,int idr,int len,int optl,int optr) {
  if (idl>idr) return;
  int posr=(idl+idr)/2;
  int posl=posr-len;
  fin=min(optr,posr-1);
  val=INF;
  for (int i=max(posl,optl);i<=fin;i++) {
    cost=dp[posl][i]+dp[i+1][posr]+abs(L[posl][i]-L[i+1][posr])+abs(R[posl][i]-R[i+1][posr]);
    if (cost<val) {
      val=cost;
      opt=i;
    }
  }
  dp[posl][posr]=val;
  dnc(idl,posr-1,len,optl,opt);
  dnc(posr+1,idr,len,opt,optr);
}

int minimum_lifts(int N, int M, vector<int> A) {
  for (int i=0;i<N;i++) {
    L[i][i]=R[i][i]=A[i];
    for (int j=i;j--;) {
      L[j][i]=min(L[j][i-1],A[i]);
      R[j][i]=max(R[j][i-1],A[i]);
    }
  }
  for (int i=1;i<N;i++) {
    dnc(i,N-1,i,0,N-2);
  }
  return dp[0][N-1]+L[0][N-1]-R[0][N-1]+M;
}
