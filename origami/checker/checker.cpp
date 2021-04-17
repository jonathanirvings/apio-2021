#include "testlib.h"

#include <cmath>

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main(int argc, char * argv[]) {
  registerChecker("origami", argc, argv);

  int N = inf.readInt();
  std::vector<int> U(N - 1), V(N - 1), W(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    U[i] = inf.readInt() - 1;
    V[i] = inf.readInt() - 1;
    W[i] = inf.readInt();
  }

  std::vector<int> degree(N, 0);
  std::vector<std::vector<int>> distance(N, std::vector<int>(N, 1e9));
  for (int i = 0; i < N - 1; ++i) {
    distance[U[i]][V[i]] = distance[V[i]][U[i]] = W[i];
    ++degree[U[i]]; ++degree[V[i]];
  }
  for (int i = 0; i < N; ++i) distance[i][i] = 0;
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        distance[i][j] = std::min(distance[i][j],
                                  distance[i][k] + distance[k][j]);
      }
    }
  }

  std::vector<int> isLeaf(N, false);
  int leafCount = 0;
  for (int i = 0; i < N; ++i) {
    if (degree[i] == 1) {
      isLeaf[i] = true;
      ++leafCount;
    }
  }
    
  std::function<double(InStream&)> getEfficiency = [&](InStream &is) {
    std::vector<double> X(N, -1), Y(N, -1);
    for (int i = 0; i < leafCount; ++i) {
      int leafIndex = is.readInt(1, N, "leafIndex") - 1;
      if (!isLeaf[leafIndex]) {
        is.quitf(_wa, "Invalid leaf index");
      }
      if (X[leafIndex] > -0.5) {
        is.quitf(_wa, "Duplicated leaf index");
      }

      X[leafIndex] = is.readDouble(0, 1, "X");
      Y[leafIndex] = is.readDouble(0, 1, "Y");
    }
    if (!ouf.seekEof()) {
      is.quitf(_wa, "Extra output found");
    }

    double efficiency = std::numeric_limits<double>::infinity();
    for (int i = 0; i < N; ++i) {
      if (!isLeaf[i]) continue;
      for (int j = i + 1; j < N; ++j) {
        if (!isLeaf[j]) continue;
        efficiency = std::min(efficiency,
                              hypot(X[i] - X[j], Y[i] - Y[j]) / distance[i][j]);
      }
    }
    return efficiency;
  };

  double score = std::min(1.0, getEfficiency(ouf) / getEfficiency(ans));
  // Ensure that there are at most 2 digits behind the decimal in score * 12.5.
  score = round(score * 1250) / 1250;
  if (score == 1.0) {
    quit(_ok);
  } else {
    quitp(score);
  }
}
