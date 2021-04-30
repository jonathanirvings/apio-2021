#include <bits/stdc++.h>
using namespace std;

const int kMaxK = 100005;

int n, m, k;
int a[kMaxK];

vector<tuple<int, int, int, int>> ans;

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < k; ++i) scanf("%d", &a[i]);
}

int main() {
  read();

  for (int i = 0; i < k; ++i) {
    ans.emplace_back(i / m, i % m, i / m + 1, i % m + 1);
  }

  for (int i = 0; i < k; ++i) {
    int x, y, xx, yy;
    tie(x, y, xx, yy) = ans[i];
    printf("%d %d %d %d\n", x, xx, y, yy);
  }
  return 0;
}
