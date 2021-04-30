#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<int> a;
vector<vector<int> > Ans;

const int MAX_N = 100005;

bool isIntersectRectangle() {
  vector<pair<int, pair<int, int> > > v;

  // 0 start segment, 1 end segment
  for (int i = 0; i < static_cast<int>(a.size()); i++) {
    // kalo ga dipasang areanya, ga usah dimasukkin biar ga sulit ngitungnya
    if (Ans[i][0] == -1 && Ans[i][1] == -1 &&
        Ans[i][2] == -1 && Ans[i][3] == -1) continue;
    v.push_back({Ans[i][0], {0, i}});
    v.push_back({Ans[i][1] - 1, {1, i}});
  }


  sort(v.begin(), v.end());

  set<pair<int, int> > st;

  for (auto data: v) {
    int type = data.second.first, index = data.second.second;

    int query_l = Ans[index][2], query_r = Ans[index][3] - 1;

    if (data.second.first == 0) {
      auto it = st.lower_bound({Ans[index][2], -1});
      if (it != st.end()) {
        int l = (*it).first, r = (*it).second;

        if(query_r >= l) return true;
      }

      if (it != st.begin()) {
        it--;
        int l = (*it).first, r = (*it).second;
        if (r >= query_l) return true;
      }

      st.insert({query_l, query_r});
    }
    else {
      st.erase({query_l, query_r});
    }
  }

  return false;
}


bool inRange(int a, int b, int c) {
  return b <= a && a <= c;
}

// check x1 <= x2 and y1 <= y2, all coordinate in the grid
bool checkInput() {
  for (auto data: Ans) {
    if (data[0] == -1 && data[1] == -1 && data[2] == -1 && data[3] == -1) continue;
    if (data[0] < data[1] && data[2] < data[3] &&
    inRange(data[0], 0, n) && inRange(data[1], 0, n) &&
    inRange(data[2], 0, m) && inRange(data[3], 0, m))
    continue;
    else return false;
  }
  return true;
}

int main(int argc, char * argv[]) {
  registerChecker("defence", argc, argv);

  n = inf.readInt();
  m = inf.readInt();
  k = inf.readInt();

  a.resize(k);
  for (int i = 0; i < k; ++i) {
    a[i] = inf.readInt();
  }

  for (int i = 0; i < k; ++i) {
    int x1, x2, y1, y2;

    x1 = ouf.readInt();
    x2 = ouf.readInt();
    y1 = ouf.readInt();
    y2 = ouf.readInt();

    vector<int> tmp = {x1, x2, y1, y2};
    Ans.push_back(tmp);
  }

  if (!ouf.seekEof()) {
    ouf.quitf(_wa, "Extra output found");
  }

  if (!checkInput()) {
    ouf.quitf(_wa, "Invalid split");
  }
  if (isIntersectRectangle()) {
    ouf.quitf(_wa, "Intersecting territories");
  }

  int score = 0;
  for (int i = 0; i < k; i++) {
    long long area_ans = 1ll * (Ans[i][1] - Ans[i][0]) * (Ans[i][3] - Ans[i][2]);

    if (area_ans == 0) {
      continue;
    }
    else if (area_ans < a[i]) score += 1;
    else if (area_ans > a[i]) score += 2;
    else if (area_ans == a[i]) score += 3;
  }

  if (score == 3 * k) {
    quit(_ok);
  } else {
    double points = 1.0 / 9 * score / k * score / k;
    points = round(points * 1000) / 1000;
    quitp(points);
  }
}
