#include "height.h"

#include <cassert>
#include <cstdio>

int main() {
  int N, Q;
  assert(2 == scanf("%d %d", &N, &Q));
  init(N);

  for (int i = 0; i < Q; ++i) {
    int L, R, H;
    assert(3 == scanf("%d %d %d", &L, &R, &H));
    printf("%d\n", add_restriction(L, R, H));
  }
  return 0;
}
