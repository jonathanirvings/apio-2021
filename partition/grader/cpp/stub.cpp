#include "partition.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main(int argc, char *argv[]) {
  assert(argc == 4);

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "a");

  int N;
  assert(fscanf(fin, "%d", &N) == 1);
  
  std::vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(fscanf(fin, "%d", &A[i]) == 1);
  }
  for (int i = 0; i < N; ++i) {
    assert(fscanf(fin, "%d", &B[i]) == 1);
  }

  init(N, A, B);

  while (true) {
    int X, Y;
    assert(fscanf(fin, "%d %d", &X, &Y) == 2);
    if (X < 0 || Y < 0) {
      break;
    }
    int partition = count_partition(X, Y);
    fprintf(fout, "%d\n", partition);
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
