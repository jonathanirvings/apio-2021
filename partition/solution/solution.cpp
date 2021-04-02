#include "partition.h"

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

vector<int> A, F;
int N;
map<int, int> compress;
vector<vector<int>> position;
vector<int> numbers;
map<pair<int, int>, int> result;

void init(int _N, std::vector<int> _A, std::vector<int> _B) {
  N = _N;
  A = _A;
  F = _B;
  position.resize(N);

  for (int i = 0; i < N; ++i) {
    numbers.push_back(A[i]);
  }
  sort(numbers.begin(), numbers.end());
  numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
  for (int i = 0; i < static_cast<int>(numbers.size()); ++i) {
    compress[numbers[i]] = i;
    position[i].clear();
    position[i].push_back(-1);
  }
  for (int i = 0; i < N; ++i) {
    position[compress[A[i]]].push_back(i);
  }
}

int count_partition(int X, int Y) {
  if (compress.count(X) == 0) {
    return 1;
  }
  X = compress[X];
  if (result.count(make_pair(X, Y)) > 0) {
    return result[make_pair(X, Y)];
  }
  int current_pos = 0;
  int partitions = 0;
  while (current_pos < static_cast<int>(position[X].size()) &&
         position[X][current_pos] < N - 1) {
    ++partitions;
    int next_true_pos = position[X][current_pos] + F[Y - 1];
    int next_pos = lower_bound(position[X].begin(), position[X].end(),
                               next_true_pos) - position[X].begin();
    next_pos = max(next_pos, current_pos + Y);
    current_pos = next_pos;
  }
  return result[make_pair(X, Y)] = partitions;
}
