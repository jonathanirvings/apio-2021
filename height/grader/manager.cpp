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
    std::string in_secret = "29ece75d26674ef1419c1cb0b6f4f53b7b3ffc76";
    std::string out_secret = "ed9ab05f5c935db30b3bcacf162c8a06196deb9e";
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

  fprintf(fout, "%d\n", N);

  std::vector<int> is_possible(Q);
  for (int i = 0; i < Q; ++i) {
    int L, R, H;
    assert(3 == scanf("%d %d %d", &L, &R, &H));
    fprintf(fout, "%d %d %d\n", L, R, H);
    fflush(fout);
    
    if (fscanf(fin, "%d", &is_possible[i]) != 1) {
      std::string out_secret = "ed9ab05f5c935db30b3bcacf162c8a06196deb9e";
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }
  fprintf(fout, "%d %d %d\n", -1, -1, -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  {
    std::string out_secret = "ed9ab05f5c935db30b3bcacf162c8a06196deb9e";
    printf("%s\n", out_secret.c_str());
    printf("OK\n");
  }
  for (int i = 0; i < Q; ++i) {
    printf("%d\n", is_possible[i]);
  }
  return 0;
}
