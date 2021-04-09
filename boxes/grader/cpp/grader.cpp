#include "boxes.h"

#include <cassert>
#include <cstdio>

#include <vector>
// BEGIN SECRET
#include <string>
// END SECRET

int main() {
  // BEGIN SECRET
  {
    std::string in_secret = "e805e23c923fcb9ae5fb27bc116eeedcaecd1814";
    std::string out_secret = "7495a6f9e0579b2eb195e1e290872916299ae955";
    char secret[1000];
    assert(1 == scanf("%s", secret));
    if (std::string(secret) != in_secret) {
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }
  // END SECRET
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }

  // BEGIN SECRET
  {
    std::string out_secret = "7495a6f9e0579b2eb195e1e290872916299ae955";
    printf("%s\n", out_secret.c_str());
    printf("OK\n");
  }
  // END SECRET
  printf("%d\n", minimum_lifts(N, M, A));
  return 0;
}
