#include "partition.h"

#include <vector>
using namespace std;

int N;
std::vector<int> A;
std::vector<int> B;

void init(int _N, std::vector<int> _A, std::vector<int> _B) {
  N = _N;
  A = _A;
  B = _B;
}

int count_partition(int X, int Y) {
  int partitions = 0;
  int elements = 0;
  int X_elements = 0;
  for (int i = 0; i < N; ++i) {
    ++elements;
    if (A[i] == X) {
      ++X_elements;
      if (X_elements >= Y && elements >= B[Y - 1]) {
        elements = 0;
        X_elements = 0;
        ++partitions;
      }
    }
  }
  if (elements > 0) {
    ++partitions;
  }
  return partitions;
}
