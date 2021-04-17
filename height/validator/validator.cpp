#include "testlib.h"

constexpr int kMaxN = 200000;
constexpr int kMaxQ = 200000;
constexpr int kMaxH = 1000000000;

int main(int, char *argv[]) {
  registerValidation();
  std::string secret = inf.readLine();
  ensuref(secret == (std::string)"29ece75d26674ef1419c1cb0b6f4f53b7b3ffc76",
          "Secret not found!");

  const char* subtask_name = argv[1];

  int maxN = kMaxN;
  int maxQ = kMaxQ;
  if (strcmp(subtask_name, "quadratic") == 0) {
    maxN = maxQ = 2000;
  } else if (strcmp(subtask_name, "sqrt-log") == 0) {
    maxN = maxQ = 50000;
  }

  int maxH = strcmp(subtask_name, "small-H") == 0 ? 20 : kMaxH;

  int N = inf.readInt(1, maxN, "N");
  inf.readSpace();
  int Q = inf.readInt(1, maxQ, "Q");
  inf.readEoln();
  
  for (int i = 0; i < Q; ++i) {
    int L = inf.readInt(0,
                        strcmp(subtask_name, "L-equals-zero") == 0 ? 0 : N - 1,
                        "L");
    inf.readSpace();
    int R = inf.readInt(L,
                        strcmp(subtask_name, "L-equals-R") == 0 ? L : N - 1,
                        "R");
    inf.readSpace();
    inf.readInt(1, maxH, "H");
    inf.readEoln();

    if (strcmp(subtask_name, "constant-difference") == 0) {
      static int query_difference = 0;
      if (i == 0) {
        query_difference = R - L;
      } else {
        ensuref(R - L == query_difference, "Query difference is not constant");
      }
    }
  }
  inf.readEof();
  return 0;
}
