#include "partition.h"

#include <map>
#include <vector>
using namespace std;

map<int, int> answer;

void init(int N, std::vector<int> A, std::vector<int> B) {
  map<int, vector<int>> position;
  for (int i = 0; i < N; ++i) {
    position[A[i]].push_back(i);
  }
  for (const pair<int, vector<int>>& p : position) {
    int key = p.first;
    const vector<int>& pos = p.second;
    int partitions = 0;
    int start = 0;
    for (int i : pos) {
      if (i - start + 1 >= B[0]) {
        ++partitions;
        start = i + 1;
      }
    }
    if (start < N) {
      ++partitions;
    }
    answer[key] = partitions;
  }
}

int count_partition(int X, int) {
  return answer.count(X) == 0 ? 1 : answer[X];
}
