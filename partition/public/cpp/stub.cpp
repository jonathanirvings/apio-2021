#include "partition.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, Q;
  assert(2 == scanf("%d %d", &N, &Q));
  std::vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &B[i]));
  }
  init(N, A, B);

  for (int i = 0; i < Q; ++i) {
    int X, Y;
    assert(2 == scanf("%d %d", &X, &Y));
    printf("%d\n", count_partition(X, Y));
  }
  return 0;
}
