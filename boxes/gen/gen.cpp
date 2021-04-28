#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> A;

void finish() {
  printf("%d %d\n", N, M);
  for (int i=0;i<N;i++) {
    printf("%d%c", A[i], " \n"[i==N-1]);
  }
}

void constantArray(int X) {
  for (int i=0;i<N;i++) {
    A.push_back(X);
  }
  finish();
}

void identityArray() {
  M = N-1;
  for (int i=0;i<N;i++) {
    A.push_back(i);
  }
  finish();
}

void dividedByM() {
  for (int i=0;i<N;i++) {
    A.push_back(rnd.next(0,1)*M);
  }
  finish();
}

void alternatingCorner() {
  A.push_back(rnd.next(0,1)*M);
  for (int i=1;i<N;i++) {
    A.push_back(M-A[i-1]);
  }
  finish();
}

void twoBlocks(int X,int L,int R) {
  for (int i=0;i<N;i++) {
    A.push_back(i<X?L:R);
  }
  finish();
}

void zigZag() {
  A.push_back(rnd.next(1,M));
  for (int i=1;i<N;i++) {
    if (i&1) A.push_back(rnd.next(0,A[i-1]-1));
    else A.push_back(rnd.next(A[i-1]+1,M));
  }
  finish();
}

void sortedArray(bool R) {
  for (int i=0;i<N;i++) {
    A.push_back(rnd.next(0,M));
  }
  sort(A.begin(),A.end());
  if (R) {
    reverse(A.begin(),A.end());
  }
  finish();
}

void randomArray(int L,int R) {
  A.push_back(L);
  A.push_back(R);
  for (int i=2;i<N;i++) {
    A.push_back(rnd.next(L,R));
    swap(A[i],A[rnd.next(0,i)]);
  }
  finish();
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 0);
  
  if (strcmp(argv[1], "constant-array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    int X = atoi(argv[4]);
    constantArray(X);
  } else if (strcmp(argv[1], "identity-array") == 0) {
    N = atoi(argv[2]);
    identityArray();
  } else if (strcmp(argv[1], "divided-by-M") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    dividedByM();
  } else if (strcmp(argv[1], "alternating-corner") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    alternatingCorner();
  } else if (strcmp(argv[1], "two-blocks") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    int X = atoi(argv[4]);
    int L = atoi(argv[5]);
    int R = atoi(argv[6]);
    twoBlocks(X, L, R);
  } else if (strcmp(argv[1], "zig-zag") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    zigZag();
  } else if (strcmp(argv[1], "sorted-non-descending") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    sortedArray(0);
  } else if (strcmp(argv[1], "sorted-non-ascending") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    sortedArray(1);
  } else if (strcmp(argv[1], "half-array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    int L = rnd.next(1, M/2);
    int R = rnd.next(M/2+1, M-1);
    randomArray(L, R);
  } else if (strcmp(argv[1], "full-array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    randomArray(0, M);
  } else {
    assert(0);
  }
}
