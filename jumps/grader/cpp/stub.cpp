#include "jumps.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main(int argc, char *argv[]) {
  assert(argc >= 3);

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "a");

  int N;
  assert(1 == fscanf(fin, "%d", &N));
  
  std::vector<int> H(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == fscanf(fin, "%d", &H[i]));
  }

  init(N, H);

  while (true) {
    int A, B, C, D;
    assert(4 == fscanf(fin, "%d %d %d %d", &A, &B, &C, &D));
    if (A < 0 || B < 0 || C < 0 || D < 0) {
      break;
    }
    fprintf(fout, "%d\n", minimum_jumps(A, B, C, D));
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
