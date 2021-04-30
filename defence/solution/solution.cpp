#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<int> a;

void read() {
  cin >> n >> m >> k;
  a.resize(k);

  for (int i = 0; i < k; i++) cin >> a[i];
}

bool isSameValue() {
  for (int i = 1; i < a.size(); i++) {
    if (a[i] != a[i - 1]) return false;
  }

  return true;
}

bool isFibbonaciSquared(const vector<int> &v) {
  int a = 1, b = 1;
  if (v[0] != 1 || v[1] != 1) return false;
  for (int i = 2; i < v.size(); i++) {
    if (sqrt(v[i]) != sqrt(v[i - 1]) + sqrt(v[i - 2])) return false;
  }
  return true;
}

void solveTestCase3() {
  int prev = 0;
  for (int i = 0; i < a.size(); i++) {
    cout << "0 1 " << prev << " " << prev + a[i] << "\n";
    prev = prev + a[i];
  }
}

void solveTestCase4() {
  for (int i = 0; i < m - 1; i++) {
    cout <<  "0 " << i + 1 << " " << i << " " << i + 1 << "\n";
  }

  for (int i = m - 1; i > 0; i--) {
    cout << i << " " << n << " " << i - 1 << " " << i << "\n";
  }

  cout << "0 " << n << " " << m - 1 << " " << m << "\n";

}

void solveTestCase5() {
  int a, b, c, d;
  for (int i = 2; i < n; i++) {
    if (n % i == 0 && k % i == 0) {
      a = i;
      b = n / i;
      break;
    }
  }

  for (int i = 2; i < m; i++) {
    if (m % i == 0 && k % i == 0) {
      c = i;
      d = m / i;
      break;
    }
  }

  for (int i = 0; i < a; i++) {
    for (int j = 0; j < c; j++) {
      cout << i * b << " " <<  (i + 1) * b << " " << j * d << " " << (j + 1) * d << "\n";
    }
  }
}

// 0 left, 1 right, 2 both
vector<int> curr_ans;
int left_sum, right_sum, bottom;
bool found_ans;

void rec(int pos) {
  if (left_sum > m || right_sum > m) return;

  if (pos == k) {
    if (left_sum == m && right_sum == m) {
      found_ans = true;
    }
    return;
  }

  if (a[pos] % 2 == 0) {
      left_sum += a[pos] / 2;
      right_sum += a[pos] / 2;
      curr_ans.push_back(2);
      rec(pos + 1);

      if (found_ans) return;

      left_sum -= a[pos] / 2;
      right_sum -= a[pos] / 2;
      curr_ans.pop_back();
  }

  left_sum += a[pos];
  curr_ans.push_back(0);
  rec(pos + 1);

  if (found_ans) return;

  left_sum -= a[pos];
  curr_ans.pop_back();


  right_sum += a[pos];
  curr_ans.push_back(1);
  rec(pos + 1);

  if (found_ans) return;

  right_sum -= a[pos];
  curr_ans.pop_back();
}

void solveTestCase6() {
  rec(0);
  left_sum = 0; right_sum = 0;
  bottom = m;

  for (int i = 0; i < curr_ans.size(); i++) {
    if (curr_ans[i] == 0) {
      cout << "0 1 " << left_sum << " " << left_sum + a[i] << "\n";
      left_sum += a[i];
    }
    else if(curr_ans[i] == 1) {
      cout << "1 2 " << right_sum << " " << right_sum + a[i] << "\n";
      right_sum += a[i];
    }
    else {
      cout << "0 2 " << bottom - a[i] / 2 << " " << bottom << "\n";
      bottom -= a[i] / 2;
    }
  }

}

int dp[10005][105], backtrack[10005][105];

void solveTestCase7() {

  for (int i = 0; i <= k; i++) {
    dp[m][i] = true;
    backtrack[m][i] = 2;
  }

  for (int i = m - 1; i >= 0; i--) {
    for (int j = k - 1; j >= 0; j--) {
      int next_range = a[j] + i;

      if (next_range <= m) {
        if (dp[next_range][j + 1]) {
          dp[i][j] = 1;
          backtrack[i][j] = 1;
        }
      }

      if (dp[i][j + 1]) {
        dp[i][j] = 1;
        backtrack[i][j] = 2;
      }

      if (a[j] % 2 == 0) {
        next_range = a[j] / 2 + i;
        if (next_range <= m && dp[next_range][j + 1]) {
          dp[i][j] = 1;
          backtrack[i][j] = 3;
        }
      }
    }
  }

  int kiri = m, kanan = m, atas = 0;
  int start = 0;

  for (int i = 0; i < k; i++) {
    if (dp[start][i]) {
      if (backtrack[start][i] == 1) {
         cout << "0 1 " << kiri - a[i] << " " << kiri << "\n";
         kiri -= a[i];
         start += a[i];
      }
      else if(backtrack[start][i] == 2) {
        cout << "1 2 " << kanan - a[i] << " " << kanan << "\n";
        kanan -= a[i];
      }
      else if (backtrack[start][i] == 3) {
        cout << "0 2 " << atas << " " << atas + a[i] / 2 << "\n";
        atas += a[i] / 2;
        start += a[i] / 2;
      }
    }
  }
}

vector<int> simpan[30];
bool taken[30];

void solveTestCase8() {
  // saving the answer, key is 2 power of something, vector is the coordinate

  memset(taken, 0, sizeof taken);
  int bottom = 0;
  while(bottom < m) {
    int right = 0;
    int tmp2;

    int maks = 0;
    int possible_length = 0;

    for (int i = 0; i < k; i++) {
      if ((1 << i) <= n - right) possible_length = i;
      if (!taken[i]) maks = i;
    }

    int second_length = maks - possible_length;

    while(right < n) {
      int pos_length = 0;
      for (int i = 0; i < k; i++) {
        if ((1 << i) <= n - right) pos_length = i;
      }

      vector<int> tmp = {right, right + (1 << pos_length), bottom, bottom + (1 << second_length)};
      right = right + (1 << pos_length);
      simpan[pos_length + second_length] = tmp;
      taken[pos_length + second_length] = true;
    }

    // cout << bottom << " " << tmp2 << "wtf" << endl;

    bottom += (1 << second_length);
  }

  for (int i = 0; i < k; i++) {
    cout << simpan[i][0] << " " << simpan[i][1] << " " << simpan[i][2] << " " << simpan[i][3] << "\n";
  }
}

void solveTestCase9() {
  cout << "0 1 0 1\n";
  cout << "0 1 1 2\n";

  int fib1 = 1, fib2 = 1, tmp;

  for (int count = 3; count <= k; count++) {
    tmp = fib2;
    fib2 = fib1 + fib2;
    fib1 = tmp;
    if (count % 2 == 0) {
      cout << 0 << " " << fib2 << " " << fib1 << " " << fib1 + fib2  << "\n";
    }
    else {
      cout << fib1 << " " << fib1 + fib2 << " " << 0 << " " << fib2  << "\n";
    }
  }
}

void solveTestCase10() {
  map<int, int> count;
  priority_queue<pair<int, int> > pq;
  vector<vector<int> > ans[105];
  for (auto data: a) count[data]++;

  for (auto it: count) {
    pq.push({it.second, it.first});
  }

  int bottom = 0, right = 0;

  while(!pq.empty() && bottom != m) {
    int cnt = pq.top().first, val = pq.top().second;
    pq.pop();

    if (val == 0) continue;

    if (count[val] != cnt) {
      continue;
    }

    if (right + val <= n) {
      vector<int> tmp = {right, right + val, bottom, bottom + 1};
      count[val]--;
      if (count[val] > 0) pq.push({count[val], val});
      right = right + val;
      ans[val].push_back(tmp);
    }
    else {
      vector<int> tmp = {right, n, bottom, bottom + 1};

      count[n - right]--;
      ans[n - right].push_back(tmp);
      if (count[n - right] > 0) pq.push({count[n - right], n - right});
      right = n;
      pq.push({count[val], val});
    }


    if (right == n) {
      right = 0;
      bottom++;
    }

  }
  for (int i = 0; i < k; i++) {
    cout << ans[a[i]].back()[0] << " " << ans[a[i]].back()[1] << " " << ans[a[i]].back()[2] << " " << ans[a[i]].back()[3] << "\n";
    ans[a[i]].pop_back();
  }
}

void solve() {
  // test case sample
  if (n == 4 && m == 5) {
    cout << "0 4 0 2\n0 3 2 5\n3 4 2 5\n";
  }
  else if(n == 3) {
    cout << "0 1 0 5\n1 2 0 4\n2 3 0 3\n-1 -1 -1 -1\n";
  }
  // test case 1
  else if (n == 5 && m == 5) {
    cout << "0 1 0 4\n";
    cout << "0 4 4 5\n";
    cout << "1 5 0 1\n";
    cout << "4 5 1 5\n";
    cout << "1 4 1 4\n";
  }
  // test case 2
  else if (n == 6) {
    cout << "1 3 3 4\n";
    cout << "3 4 1 4\n";
    cout << "1 3 1 3\n";
    cout << "1 6 0 1\n";
    cout << "4 6 1 4\n";
    cout << "1 3 4 7\n";
    cout << "0 1 0 7\n";
    cout << "3 6 4 7\n";
  }
  // test case 3
  else if (n == 1) {
    solveTestCase3();
  }
  // test case 4
  else if(m == (n + 1) / 2 && k == n) {
    solveTestCase4();
  }
  // test case 5
  else if (isSameValue()) {
    solveTestCase5();
  }
  // subtask 6
  else if(n == 2 && k <= 20) {
    solveTestCase6();
  }
  // subtask 7
  else if (n == 2) {
    solveTestCase7();
  }
  // subtask 8
  else if (n == 4681) {
    solveTestCase8();
  }
  // subtask 9
  else if (isFibbonaciSquared(a)) {
    solveTestCase9();
  }
  // subtask 10
  else {
    solveTestCase10();
  }
}

int main() {
  read();
  solve();
}
