#include "testlib.h"

#include <functional>
#include <numeric>
#include <vector>

int main() {
  registerValidation();
  int N = inf.readInt(3, 12, "N");
  inf.readEoln();

  std::vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    U[i] = inf.readInt(1, N, "U");
    inf.readSpace();
    V[i] = inf.readInt(1, N, "V");
    inf.readSpace();
    inf.readInt(1, 4, "W");
    inf.readEoln();
  }
  inf.readEof();

  ensuref([](const std::vector<int> &U, const std::vector<int> &V) {
    std::vector<int> par(U.size() + 1);
    std::iota(par.begin(), par.end(), 0);
    std::function<int(int)> root = [&root, &par](int u) {
      if (u == par[u]) return u;
      return par[u] = root(par[u]);
    };

    for (int i = 0; i < static_cast<int>(U.size()); ++i) {
      if (root(U[i] - 1) == root(V[i] - 1)) return false;
      par[par[V[i] - 1]] = par[U[i] - 1];
    }
    return true;
  }(U, V), "Given edges do not form a tree!");
  return 0;
}
