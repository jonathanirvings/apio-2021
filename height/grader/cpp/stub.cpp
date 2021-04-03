#include "height.h"

#include <cassert>
#include <cstdio>

int main(int argc, char *argv[]) {
  assert(argc >= 3);

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "a");

  int N;
  assert(1 == fscanf(fin, "%d", &N));

  init(N);

  while (true) {
    int L, R, H;
    assert(3 == fscanf(fin, "%d %d %d", &L, &R, &H));
    if (L < 0 || R < 0 || H < 0) {
      break;
    }
    fprintf(fout, "%d\n", add_restriction(L, R, H));
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
