#include "testlib.h"

#include <cassert>
#include <csignal>
#include <cstdio>

// TODO: Fill solution
namespace solution {

void init(int N) {

}

int add_restriction(int L, int R, int H) {
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

  fprintf(fout, "%d\n", N);
  solution::init(N);

  bool correct_answer = true;
  for (int i = 0; i < Q; ++i) {
    int L, R, H;
    assert(3 == scanf("%d %d %d", &L, &R, &H));
    fprintf(fout, "%d %d %d\n", L, R, H);
    fflush(fout);
    
    int is_possible;
    if (fscanf(fin, "%d", &is_possible) != 1) {
      quitf(_wa, "Could not read response");
    }
    if (is_possible != solution::add_restriction(L, R, H)) {
      correct_answer = false;
    }
  }
  fprintf(fout, "%d %d %d\n", -1, -1, -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  if (!correct_answer) {
    quitf(_wa, "Wrong response");
  }
  quit(_ok);
}
