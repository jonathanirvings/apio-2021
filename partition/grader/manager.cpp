#include "testlib.h"

#include <cassert>
#include <csignal>
#include <cstdio>

#include <vector>

namespace solution {

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

}  // namespace solution

int main(int argc, char *argv[]) {
  testlibMode = _checker;
  ouf.mode = _output;

  assert(argc >= 3);

  {
    // Keep alive on broken pipes
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
  }

  // Must be in this order
  FILE *fout = fopen(argv[2], "a");
  FILE *fin = fopen(argv[1], "r");

  int N, Q;
  assert(2 == scanf("%d %d", &N, &Q));

  std::vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &B[i]));
  }

  fprintf(fout, "%d\n", N);
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      fprintf(fout, " ");
    }
    fprintf(fout, "%d", A[i]);
  }
  fprintf(fout, "\n");
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      fprintf(fout, " ");
    }
    fprintf(fout, "%d", B[i]);
  }
  fprintf(fout, "\n");
  fflush(fout);
  solution::init(N, A, B);

  bool correct_answer = true;
  for (int i = 0; i < Q; ++i) {
    int X, Y;
    assert(2 == scanf("%d %d", &X, &Y));
    fprintf(fout, "%d %d\n", X, Y);
    fflush(fout);
    
    int partition;
    if (fscanf(fin, "%d", &partition) != 1) {
      quitf(_wa, "Could not read response");
    }
    if (partition != solution::count_partition(X, Y)) {
      correct_answer = false;
    }
  }
  fprintf(fout, "%d %d\n", -1, -1);
  fflush(fout);

  fclose(fin);
  fclose(fout);

  if (!correct_answer) {
    quitf(_wa, "Wrong response");
  }
  quit(_ok);
}
