#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
vector<int> A;

vector<int> generateRandomArraySumToK(int k, int maxValue) {
  vector<int> v;

  vector<int> diff;
  for (int i = 0; i < k - 1; i++) {
    diff.push_back(rnd.next(1, maxValue));
  }

  sort(diff.begin(), diff.end());
  v.push_back(diff[0]);

  for (int i = 1; i < static_cast<int>(diff.size()); i++) {
    diff[i] = max(diff[i], diff[i - 1] + 1);
    v.push_back(diff[i] - diff[i - 1]);
  }

  if (maxValue <= diff.back()) return generateRandomArraySumToK(k, maxValue);

  v.push_back(maxValue - diff.back());
  return v;
}

void generateRandomArray(int k, int maxValue) {
  A = generateRandomArraySumToK(k, maxValue);
}

void generateOddEven(int o, int e, int maxVal) {
  vector<int> v = generateRandomArraySumToK(o + e, maxVal);

  vector<int> odd, even;
  for (auto data: v) {
    if (data % 2 == 1) odd.push_back(data);
    else even.push_back(data);
  }

  while(static_cast<int>(odd.size()) > o) {
      even.push_back(odd.back() + 1);
      odd.pop_back();
      even.push_back(odd.back() - 1);
      odd.pop_back();
  }

  while(static_cast<int>(even.size()) > e) {
    odd.push_back(even.back() + 1);
    even.pop_back();
    odd.push_back(even.back() - 1);
    even.pop_back();
  }

  A.insert(A.end(), odd.begin(), odd.end());
  A.insert(A.end(), even.begin(), even.end());
}

// generate increment
void generateTestCase4(int k) {
  for (int i = 0; i < k; i++) A.push_back(i + 1);
}

void generateTestCase5(int k, int val) {
  for (int i = 0; i < k; i++) A.push_back(val);
}

void generateTestCase6(int k, int maxVal) {
  int sum = 0;
  for (int i = 0; i < k/4; i++) {
    A.push_back(2 * rnd.next(1, 2 * maxVal / k));
    sum += A.back() / 2;
  }

  if (sum % 2 == 1) {
    A[0] += 2;
    sum++;
  }

  generateOddEven(4, 3, maxVal - sum);
  generateOddEven(6, 2, maxVal - sum);

  shuffle(A.begin(), A.end());
}

void generatePowerOf2Array(int k) {
  for (int i = 0; i < k; i++) {
    A.push_back(1 << i);
  }
}

void generateFibbonaciSquaredArray(int k) {
  A.push_back(1); A.push_back(1);
  for (int i = 2; i < k; i++) {
    A.push_back(pow(sqrt(A[i - 1]) + sqrt(A[i - 2]), 2));
  }
}

void generateTestCase10(int k) {
  while(k) {
    int val = min(rnd.next(1, 100), k);
    A.push_back(val);
    k -= val;
  }

  K = A.size();
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 0);

  if (strcmp(argv[1], "random_array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generateRandomArray(K, N * M);
  } else if (strcmp(argv[1], "test_case_4") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generateTestCase4(K);
  } else if (strcmp(argv[1], "test_case_5") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generateTestCase5(K, 1LL * N * M / K);
  } else if (strcmp(argv[1], "test_case_6") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generateTestCase6(K, M);
  } else if (strcmp(argv[1], "power_of_2_array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generatePowerOf2Array(K);
  } else if (strcmp(argv[1], "fibonacci_squared_array") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    K = atoi(argv[4]);
    generateFibbonaciSquaredArray(K);
  } else if (strcmp(argv[1], "test_case_10") == 0) {
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    generateTestCase10(N * M);
  } else {
    assert(0);
  }

  printf("%d %d %d\n", N, M, K);
  for (int i = 0; i < K; ++i) {
    printf("%d%c", A[i], " \n"[i == K - 1]);
  }
  return 0;
}
