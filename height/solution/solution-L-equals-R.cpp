#include "height.h"

#include <algorithm>
#include <vector>

int answer;
std::vector<int> H;

void init(int N) {
  H.assign(N, -1);
  answer = 1;
}

int add_restriction(int L, int, int X) {
  if (answer == 0) return 0;
  if (H[L] != -1 && H[L] != X) return answer = 0;
  H[L] = X;
  return 1;
}
