#include "testlib.h"

#include <vector>

constexpr int kMaxN = 100000;
constexpr int kMaxQ = 100000;
constexpr int kMaxA = 1000000000;
constexpr int kMaxX = 1000000000;

int main(int, char *argv[]) {
  registerValidation();

  const char* subtask_name = argv[1];

  int maxQ = (strcmp(subtask_name, "Q-less-than-five") == 0 ? 5 : kMaxQ);

  int N = inf.readInt(1, kMaxN, "N");
  inf.readSpace();
  int Q = inf.readInt(1, maxQ, "Q");
  inf.readEoln();
  
  inf.readInts(N, 1, kMaxA, "A");
  inf.readEoln();
  std::vector<int> B = inf.readInts(N, 1, N, "B");
  inf.readEoln();

  if (strcmp(subtask_name, "B_i-equals-i") == 0) {
    for (int i = 0; i < N; ++i) {
      ensuref(B[i] == i + 1, "Found B_i != i");
    }
  }

  int maxY = (strcmp(subtask_name, "Y-equals-one") == 0 ? 1 : N);
  int maxX = (strcmp(subtask_name, "X-equals-one") == 0 ? 1 : kMaxX);
  
  for (int i = 0; i < Q; ++i) {
    inf.readInt(1, maxX, "X");
    inf.readSpace();
    inf.readInt(1, maxY, "Y");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
