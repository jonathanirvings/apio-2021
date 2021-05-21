#include "height.h"

#include <cassert>
#include <cstdio>

int main() {
  int N;
  assert(1 == scanf("%d", &N));

  init(N);

  while (true) {
    int L, R, H;
    assert(3 == scanf("%d %d %d", &L, &R, &H));
    if (L < 0 || R < 0 || H < 0) {
      break;
    }
    printf("%d\n", add_restriction(L, R, H));
    fflush(stdout);
  }
  return 0;
}
