#include "testlib.h"

#include <string.h>

#include <string>
#include <vector>

const int kMaxN = 2000;
const int kMaxM = 100000;

int main(int, char *argv[]) {
  registerValidation();
  std::string secret = inf.readLine();
  ensuref(secret == (std::string)"e805e23c923fcb9ae5fb27bc116eeedcaecd1814",
          "Secret not found!");

  const char* subtask_name = argv[1];

  int maxN = kMaxN;
  int maxM = kMaxM;
  if (strcmp(subtask_name, "bruteforce") == 0) {
    maxN = maxM = 10;
  } else if (strcmp(subtask_name, "exponential") == 0) {
    maxN = maxM = 20;
  } else if (strcmp(subtask_name, "fifth") == 0) {
    maxN = maxM = 30;
  } else if (strcmp(subtask_name, "cubic") == 0) {
    maxN = 200;
  }
  
  int N = inf.readInt(1, maxN, "N");
  inf.readSpace();
  int M = inf.readInt(1, maxM, "M");
  inf.readEoln();

  std::vector<int> A = inf.readInts(N, 0, M, "A");
  inf.readEoln();

  if (strcmp(subtask_name, "M-divides-A_i") == 0) {
    for (int i = 0; i < N; ++i) {
      ensuref(A[i] % M == 0, "A_i is not divisible by M");
    }
  } else if (strcmp(subtask_name, "A_i-equals-i") == 0) {
    ensuref(N == M + 1, "N is not equal to M + 1");
    for (int i = 0; i < N; ++i) {
      ensuref(A[i] == i, "A_i is not equal to i"); 
    }
  }

  inf.readEof();
  return 0;
}
