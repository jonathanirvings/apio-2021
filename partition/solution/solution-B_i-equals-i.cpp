#include "partition.h"

#include <map>
using namespace std;

map<int, int> cnt;
int last;

void init(int N, std::vector<int> A, std::vector<int>) {
  for (int a : A) {
    ++cnt[a];
  }
  last = A[N - 1];
}

int count_partition(int X, int Y) {
  if (cnt.count(X) == 0) {
    return 1;
  }
  int answer = cnt[X] / Y;
  if (last != X || cnt[X] > answer * Y) {
    ++answer;
  }
  return answer;
}
