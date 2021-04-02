#include "partition.h"

#include <algorithm>
#include <vector>
using namespace std;

constexpr int kInterestingElement = 1;

vector<int> answer;

void init(int N, std::vector<int> A, std::vector<int> B) {
  vector<int> position;
  for (int i = 0; i < N; ++i) {
    if (A[i] == kInterestingElement) {
      position.push_back(i);
    }
  }
  for (int i = 1; i <= N; ++i) {
    int partitions = 0;
    int start = 0;
    int ix = -1;
    while (start < N) {
      ++partitions;
      int next_ix = max(
          static_cast<int>(
              lower_bound(position.begin(), position.end(),
                          start + B[i - 1] - 1) - position.begin()),
          ix + i);
      if (next_ix < static_cast<int>(position.size())) {
        ix = next_ix;
        start = position[ix] + 1;
      } else {
        break;
      }
    }
    answer.push_back(partitions);
  }
}

int count_partition(int, int Y) {
  return answer[Y - 1];
}
