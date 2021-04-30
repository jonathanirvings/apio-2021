#include "hoax.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main(int argc, char *argv[]) {
  assert(argc >= 3);

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "a");

  int N, S;
  assert(2 == fscanf(fin, "%d %d", &N, &S));

  std::vector<int> T(N);
  std::vector<std::vector<int>> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == fscanf(fin, "%d", &T[i]));
    A[i].resize(T[i]);
    B[i].resize(T[i]);
    for (int j = 0; j < T[i]; ++j) {
      assert(2 == fscanf(fin, "%d %d", &A[i][j], &B[i][j]));
    }
  }

  init(N, S, T, A, B);

  while (true) {
    int P;
    assert(1 == fscanf(fin, "%d", &P));
    if (P < 0) {
      break;
    }
    fprintf(fout, "%d\n", count_users(P));
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
