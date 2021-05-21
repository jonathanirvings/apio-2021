#include <cassert>
#include <csignal>
#include <cstdio>

#include <string>
#include <vector>

int main(int argc, char *argv[]) {
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

  {
    std::string in_secret = "ini-adalah-masukan-rahasia";
    std::string out_secret = "ini-adalah-keluaran-rahasia";
    char secret[1000];
    assert(1 == scanf("%s", secret));
    if (std::string(secret) != in_secret) {
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }

  int N, S, Q;
  assert(3 == scanf("%d %d %d", &N, &S, &Q));

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

  fprintf(fout, "%d %d\n", N, S);
  for (int i = 0; i < N; ++i) {
    fprintf(fout, "%d", T[i]);
    for (int j = 0; j < T[i]; ++j) {
      fprintf(fout, " %d %d", A[i][j], B[i][j]);
    }
    fprintf(fout, "\n");
  }
  fflush(fout);

  std::vector<int> users(Q);
  for (int i = 0; i < Q; ++i) {
    int P;
    assert(1 == scanf("%d", &P));
    fprintf(fout, "%d\n", P);
    fflush(fout);

    {
      std::string in_secret = "Q";
      std::string out_secret = "ini-adalah-keluaran-rahasia";
      char secret[100];
      if (fscanf(fin, "%s", secret) != 1 || std::string(secret) != in_secret) {
        printf("%s\n", out_secret.c_str());
        printf("SV\n");
        fclose(stdout);
        return 0;
      }
    }

    if (fscanf(fin, "%d", &users[i]) != 1) {
      std::string out_secret = "ini-adalah-keluaran-rahasia";
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }
  fprintf(fout, "%d\n", -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  {
    std::string out_secret = "ini-adalah-keluaran-rahasia";
    printf("%s\n", out_secret.c_str());
    printf("OK\n");
  }
  for (int i = 0; i < Q; ++i) {
    printf("%d\n", users[i]);
  }
  return 0;
}
