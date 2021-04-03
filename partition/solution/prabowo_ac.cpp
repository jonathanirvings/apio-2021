#include "partition.h"

#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> B;
vector<int> comp;
vector<vector<int>> pos;

void init(int _N, std::vector<int> A, std::vector<int>_B) {
  N = _N; B = _B;
  comp = A;
  sort(comp.begin(), comp.end());
  comp.resize(unique(comp.begin(), comp.end()) - comp.begin());

  pos.resize(comp.size());
  for (int i = 0; i < N; ++i) {
    pos[lower_bound(comp.begin(), comp.end(), A[i]) - comp.begin()].push_back(i);
  }
}

map<pair<int, int>, int> memo;
int count_partition(int X, int Y) {
  int idx = lower_bound(comp.begin(), comp.end(), X) - comp.begin();
  if (idx == static_cast<int>(comp.size()) || comp[idx] != X) return 1;
  if (memo.find({idx, Y}) != memo.end()) return memo[{idx, Y}];

  int ret = 0;
  int cur = -1;
  while (cur + Y < static_cast<int>(pos[idx].size())) {
    int nxt = (cur < 0 ? -1 : pos[idx][cur]) + B[Y - 1];
    nxt = lower_bound(pos[idx].begin(), pos[idx].end(), nxt) - pos[idx].begin();
    if (nxt == static_cast<int>(pos[idx].size())) break;
    cur = max(cur + Y, nxt);
    ++ret;
  }

  if (cur == -1 || pos[idx][cur] != N - 1) ++ret;
  return memo[{idx, Y}] = ret;
}
