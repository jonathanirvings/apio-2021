#include "testlib.h"

#include <numeric>
#include <vector>

const int kMaxN = 1'000'000'000;
const int kMaxK = 100000;

int main(int, char* argv[]) {
  registerValidation();

  const char* subtask_name = argv[1];

  int subtask = -1;
  if (strcmp(subtask_name, "subtask1") == 0) {
    subtask = 1;
  } else if (strcmp(subtask_name, "subtask2") == 0) {
    subtask = 2;
  } else if (strcmp(subtask_name, "subtask3") == 0) {
    subtask = 3;
  } else if (strcmp(subtask_name, "subtask4") == 0) {
    subtask = 4;
  } else if (strcmp(subtask_name, "subtask5") == 0) {
    subtask = 5;
  } else if (strcmp(subtask_name, "subtask6") == 0) {
    subtask = 6;
  } else if (strcmp(subtask_name, "subtask7") == 0) {
    subtask = 7;
  } else if (strcmp(subtask_name, "subtask8") == 0) {
    subtask = 8;
  } else if (strcmp(subtask_name, "subtask9") == 0) {
    subtask = 9;
  } else if (strcmp(subtask_name, "subtask10") == 0) {
    subtask = 10;
  }

  int N = std::vector<int>({
      5, 6, 1, 99999, 9973 * 293, 2, 2, 4681, 46368, 2000
  }).at(subtask - 1);
  int M = std::vector<int>({
      5, 7, kMaxN, 50000, 99991 * 311, kMaxN, 10000, 229383, 28657, 2000
  }).at(subtask - 1);
  int K = std::vector<int>({
      5, 8, 100000, 99999, 293 * 311, 20, 100, 30, 23, 79191
  }).at(subtask - 1);

  ensuref(inf.readInt(1, kMaxN, "N") == N, "N does not match");
  inf.readSpace();
  ensuref(inf.readInt(1, kMaxN, "M") == M, "M does not match");
  inf.readSpace();
  ensuref(inf.readInt(1, kMaxK, "K") == K, "K does not match");
  inf.readEoln();

  std::vector<int> A = inf.readInts(K, 1, kMaxN, "A");
  ensuref(std::accumulate(A.begin(), A.end(), 0LL) == 1LL * N * M,
          "Sum of A is not equal to N*M");
  inf.readEoln();
  inf.readEof();

  if (subtask == 1) {
    ensuref(std::vector<int>({4, 4, 4, 4, 9}) == A, "A does not match");
  } else if (subtask == 2) {
    ensuref(std::vector<int>({2, 3, 4, 5, 6, 6, 7, 9}) == A, "A does not match");
  } else if (subtask == 4) {
    ensuref([&A]() {
      for (int i = 0; i < static_cast<int>(A.size()); ++i) {
        if (A[i] != i + 1) return false;
      }
      return true;
    }(), "A_i != i + 1");
  } else if (subtask == 5) {
    ensuref(std::vector<int>(K, 9973 * 99991) == A, "A does not match");
  } else if (subtask == 6) {
    ensuref(std::accumulate(A.begin(), A.end(), 0, [](int cnt, int a) {
      return cnt + (a % 2 == 0);
    }) == 10, "Number of even values in A does not match");
    ensuref(std::accumulate(A.begin(), A.end(), 0, [](int cnt, int a) {
      return cnt + (a % 2 == 1);
    }) == 10, "Number of odd values in A does not match");
  } else if (subtask == 8) {
    ensuref([&A]() {
      for (int i = 0; i < static_cast<int>(A.size()); ++i) {
        if (A[i] != 1 << i) return false;
      }
      return true;
    }(), "A_i != 2^i");
  } else if (subtask == 9) {
    ensuref([&A]() {
      if (A[0] != 1 || A[1] != 1) return false;
      int a = 1, b = 1, c = -1;
      for (int i = 2; i < static_cast<int>(A.size()); ++i) {
        c = a + b; a = b; b = c;
        if (A[i] != c * c) return false;
      }
      return true;
    }(), "A is not fibonacci squared");
  } else if (subtask == 10) {
    ensuref(all_of(A.begin(), A.end(), [](int a) { return a <= 100; }),
            "Some values in A are too large");
  }

  return 0;
}
