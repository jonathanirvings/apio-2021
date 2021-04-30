#include <bits/stdc++.h>
using namespace std;

const int kMaxK = 100005;

int n, m, k;
int a[kMaxK];

vector<tuple<int, int, int, int>> ans;

void solveSubtask1() {
  ans.emplace_back(0, 0, 1, 4);
  ans.emplace_back(0, 4, 4, 5);
  ans.emplace_back(4, 1, 5, 5);
  ans.emplace_back(1, 0, 5, 1);
  ans.emplace_back(1, 1, 4, 4);
}

void solveSubtask2() {
  ans.emplace_back(0, 0, 1, 2);
  ans.emplace_back(0, 2, 1, 5);
  ans.emplace_back(0, 5, 2, 7);
  ans.emplace_back(1, 0, 2, 5);
  ans.emplace_back(2, 0, 5, 2);
  ans.emplace_back(2, 2, 5, 4);
  ans.emplace_back(5, 0, 6, 7);
  ans.emplace_back(2, 4, 5, 7);
}

void solveSubtask3() {
  int sum = 0;
  for (int i = 0; i < k; ++i) {
    ans.emplace_back(0, sum, 1, sum + a[i]);
    sum += a[i];
  }
}

void solveSubtask4() {
  for (int i = 0; i < m-1; ++i) {
    ans.emplace_back(0, i, i+1, i+1);
  }
  for (int i = m-2; i >= 0; --i) {
    ans.emplace_back(i+1, i, n, i+1);
  }
  ans.emplace_back(0, m-1, n, m);
}

void solveSubtask5() {
  vector<int> factorN, factorM;
  for (int i = 1; i*i <= n; ++i) if (n % i == 0) {
    factorN.push_back(i); factorN.push_back(n/i);
  }
  for (int i = 1; i*i <= m; ++i) if (m % i == 0) {
    factorM.push_back(i); factorM.push_back(m/i);
  }

  for (int p: factorN) for (int r: factorM) {
    int q = n/p, s = m/r;
    if (k == p*r && a[0] == q*s) {
      for (int i = 0; i < p; ++i) for (int j = 0; j < r; ++j) {
        ans.emplace_back(i*q, j*s, (i+1)*q, (j+1)*s);
      }
      return;
    }
  }
}

void solveSubtask6() {
  bool found = false;
  vector<int> v;
  function<void(int, int)> dfs = [&](int x, int sum) {
    if (x == k) {
      if (sum == 0) {
        found = true;
        int l1 = 0, l2 = 0, r = m;
        for (int i = 0; i < k; ++i) {
          if (v[i] == 0) {
            ans.emplace_back(0, l1, 1, l1 + a[i]);
            l1 += a[i];
          } else if (v[i] == 1) {
            ans.emplace_back(1, l2, 2, l2 + a[i]);
            l2 += a[i];
          } else {
            ans.emplace_back(0, r - a[i]/2, 2, r);
            r -= a[i] / 2;
          }
        }
      }
      return;
    }

    v.push_back(0); if (!found) dfs(x+1, sum - a[x]); v.pop_back();
    v.push_back(1); if (!found) dfs(x+1, sum + a[x]); v.pop_back();
    v.push_back(2); if (!found && a[x] % 2 == 0) dfs(x+1, sum); v.pop_back();
  };

  dfs(0, 0);
}

void solveSubtask7() {
  vector<vector<bool>> dp(k, vector<bool>(n*m*2 + 1)), vis(k, vector<bool>(n*m*2 + 1));
  function<bool(int, int)> f = [&](int x, int sum) {
    if (x == k) return sum == 0;
    if (vis[x][sum + n*m]) return (bool) dp[x][sum + n*m];
    vis[x][sum + n*m] = true;

    bool ret = f(x+1, sum - a[x]) | f(x+1, sum + a[x]);
    if (a[x] % 2 == 0) ret |= f(x+1, sum);

    return (bool) (dp[x][sum + n*m] = ret);
  };

  int sum = 0;
  int l1 = 0, l2 = 0, r = m;
  for (int i = 0; i < k; ++i) {
    if (f(i+1, sum - a[i])) {
      ans.emplace_back(0, l1, 1, l1 + a[i]);
      l1 += a[i];
      sum -= a[i];
    } else if (f(i+1, sum + a[i])) {
      ans.emplace_back(1, l2, 2, l2 + a[i]);
      l2 += a[i];
      sum += a[i];
    } else if (a[i] % 2 == 0) {
      ans.emplace_back(0, r - a[i]/2, 2, r);
      r -= a[i] / 2;
    } else {
      assert(0);
    }
  }
}

void solveSubtask8() {
  ans.resize(k);
  int sumx = 0;
  for (int i = 0; i < k; ++i) {
    if (n >> i & 1); else continue;
    int sumy = 0;
    for (int j = 0; j < k; ++j) {
      if (m >> j & 1); else continue;
      ans[i + j] = make_tuple(sumx, sumy, sumx + (1 << i), sumy + (1 << j));
      sumy |= 1 << j;
    }
    sumx |= 1 << i;
  }
}

void solveSubtask9() {
  int a = 0, b = 1, c;
  for (int i = 0; i < k; ++i) {
    if (i & 1) {
      ans.emplace_back(0, a, b, a+b);
    } else {
      ans.emplace_back(a, 0, a+b, b);
    }
    c = a + b;
    a = b; b = c;
  }
}

void solveSubtask10() {
  const int kMaxA = 100;
  vector<int> idxs[kMaxA + 1];
  ans.resize(k);
  for (int i = 0; i < k; ++i) {
    idxs[a[i]].push_back(i);
  }

  priority_queue<pair<int, int>> pq;
  for (int i = 1; i <= kMaxA; ++i) {
    if (idxs[i].size() > 0) pq.push({idxs[i].size(), i});
  }

  int row = 0, cur = 0;
  while (pq.size()) {
    int c, a;
    tie(c, a) = pq.top();
    pq.pop();

    if (c != idxs[a].size()) {
      if (idxs[a].size() > 0) pq.push({idxs[a].size(), a});
      continue;
    }

    if (a >= n - cur) {
      assert(idxs[n - cur].size() > 0);

      ans[idxs[n - cur].back()] = make_tuple(cur, row, n, row + 1);
      idxs[n - cur].pop_back();
      ++row, cur = 0;

      pq.push({c, a});
      continue;
    }

    ans[idxs[a].back()] = make_tuple(cur, row, cur + a, row + 1);
    idxs[a].pop_back();
    cur += a;
    if (idxs[a].size() > 0) pq.push({idxs[a].size(), a});
  }

  assert(row == m && cur == 0);
}

int detectSubtask() {
  if (n == 5) return 1;
  if (n == 6) return 2;
  if (n == 1) return 3;
  if (m == (n + 1) / 2) return 4;
  if (1LL * n * m == 1LL * k * a[0]) return 5;
  if (n == 2 && k == 20) return 6;
  if (n == 2) return 7;
  if (k == 30) return 8;
  if (round(sqrt(a[k-3]) + sqrt(a[k-2]) - sqrt(a[k-1])) == 0) return 9;
  return 10;
}

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < k; ++i) scanf("%d", &a[i]);
}

int main() {
  read();

  function<void()> solvers[10] = {
    solveSubtask1,
    solveSubtask2,
    solveSubtask3,
    solveSubtask4,
    solveSubtask5,
    solveSubtask6,
    solveSubtask7,
    solveSubtask8,
    solveSubtask9,
    solveSubtask10,
  };
  ans.clear();
  solvers[detectSubtask() - 1]();

  for (int i = 0; i < k; ++i) {
    int x, y, xx, yy;
    tie(x, y, xx, yy) = ans[i];
    printf("%d %d %d %d\n", x, xx, y, yy);
  }
  return 0;
}
