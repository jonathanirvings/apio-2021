#include "height.h"

#include <set>

int answer;
std::set<std::pair<int, int>> queries;

void init(int) {
  queries.clear();
  answer = 1;
}

int add_restriction(int, int R, int X) {
  if (answer == 0) return 0;
  auto it = queries.lower_bound({R, -1});
  if (it != queries.end() && it->first == R) {
    if (it->second != X) return answer = 0;
    ++it;
  }

  if (it != queries.end() && it->second < X) return answer = 0;
  it = queries.insert({R, X}).first;
  if (it != queries.begin() && std::prev(it)->second > X) return answer = 0;

  return 1;
}
