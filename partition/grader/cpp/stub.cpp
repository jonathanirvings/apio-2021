#include "partition.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main(int argc, char *argv[]) {
  assert(argc >= 3);

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "a");

  int N;
  assert(1 == fscanf(fin, "%d", &N));
  
  std::vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == fscanf(fin, "%d", &A[i]));
  }
  for (int i = 0; i < N; ++i) {
    assert(1 == fscanf(fin, "%d", &B[i]));
  }

  init(N, A, B);

  while (true) {
    int X, Y;
    assert(2 == fscanf(fin, "%d %d", &X, &Y));
    if (X < 0 || Y < 0) {
      break;
    }
    fprintf(fout, "%d\n", count_partition(X, Y));
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
