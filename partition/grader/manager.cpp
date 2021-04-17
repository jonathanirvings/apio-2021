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

  int N, Q;
  assert(2 == scanf("%d %d", &N, &Q));

  std::vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &B[i]));
  }

  fprintf(fout, "%d\n", N);
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      fprintf(fout, " ");
    }
    fprintf(fout, "%d", A[i]);
  }
  fprintf(fout, "\n");
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      fprintf(fout, " ");
    }
    fprintf(fout, "%d", B[i]);
  }
  fprintf(fout, "\n");
  fflush(fout);

  std::vector<int> partition(Q);
  for (int i = 0; i < Q; ++i) {
    int X, Y;
    assert(2 == scanf("%d %d", &X, &Y));
    fprintf(fout, "%d %d\n", X, Y);
    fflush(fout);
    
    if (fscanf(fin, "%d", &partition[i]) != 1) {
      std::string out_secret = "ini-adalah-keluaran-rahasia";
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }
  fprintf(fout, "%d %d\n", -1, -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  {
    std::string out_secret = "ini-adalah-keluaran-rahasia";
    printf("%s\n", out_secret.c_str());
    printf("OK\n");
  }
  for (int i = 0; i < Q; ++i) {
    printf("%d\n", partition[i]);
  }
  return 0;
}
