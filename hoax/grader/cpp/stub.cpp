#include "hoax.h"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

int main() {
  int N, S;
  assert(2 == scanf("%d %d", &N, &S));

  std::vector<int> T(N);
  std::vector<std::vector<int>> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &T[i]));
    A[i].resize(T[i]);
    B[i].resize(T[i]);
    for (int j = 0; j < T[i]; ++j) {
      assert(2 == scanf("%d %d", &A[i][j], &B[i][j]));
    }
  }

  init(N, S, T, A, B);

  while (true) {
    int P;
    if (scanf("%d", &P) != 1) {
      return 0;
    }
    if (P < 0) {
      break;
    }

    int result = count_users(P);
    {
      std::string out_secret = "Q";
      printf("%s\n", out_secret.c_str());
    }
    printf("%d\n", result);
    fflush(stdout);
  }
  return 0;
}
