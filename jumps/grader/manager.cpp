#include "testlib.h"

#include <cassert>
#include <csignal>
#include <cstdio>

#include <vector>

// TODO: Fill solution
namespace solution {

#include <vector>

void init(int N, std::vector<int> H) {

}

int minimum_jumps(int A, int B, int C, int D) {
  return 0;
}

}  // namespace solution

int main(int argc, char *argv[]) {
  testlibMode = _checker;
  ouf.mode = _output;

  assert(argc >= 3);

  {
    // Keep alive on broken pipes
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
  }

  // Must be in this order
  FILE *fout = fopen(argv[2], "a");
  FILE *fin = fopen(argv[1], "r");

  int N, Q;
  assert(2 == scanf("%d %d", &N, &Q));

  std::vector<int> H(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &H[i]));
  }

  fprintf(fout, "%d\n", N);
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      fprintf(fout, " ");
    }
    fprintf(fout, "%d", H[i]);
  }
  fprintf(fout, "\n");
  fflush(fout);
  solution::init(N, H);

  bool correct_answer = true;
  for (int i = 0; i < Q; ++i) {
    int A, B, C, D;
    assert(4 == scanf("%d %d %d %d", &A, &B, &C, &D));
    fprintf(fout, "%d %d %d %d\n", A, B, C, D);
    fflush(fout);
    
    int jumps;
    if (fscanf(fin, "%d", &jumps) != 1) {
      quitf(_wa, "Could not read response");
    }
    if (jumps != solution::minimum_jumps(A, B, C, D)) {
      correct_answer = false;
    }
  }
  fprintf(fout, "%d %d %d %d\n", -1, -1, -1, -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  if (!correct_answer) {
    quitf(_wa, "Wrong response");
  }
  quit(_ok);
}
