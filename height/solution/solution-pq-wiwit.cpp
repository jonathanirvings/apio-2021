#include "height.h"
#include <bits/stdc++.h>

using namespace std;

struct SegTree {
  int n;
  vector<int> maxi;
  vector<priority_queue<int>> potentials;

  void init(int _n) {
    n = _n;
    maxi.assign(2 * n, 2e9);
    potentials.resize(2 * n);
  }

  inline void upd(int id, int v) {
    if (maxi[id] > v) {
      maxi[id] = v;
      while (!potentials[id].empty() && potentials[id].top() > v)
        potentials[id].pop();
      if (potentials[id].empty() || potentials[id].top() < v)
        potentials[id].push(v);
    }
  }

  inline void push_down(int id, int il, int ir) {
    upd(il, maxi[id]);
    upd(ir, maxi[id]);
  }

  void update(int x, int y, int v, set<int>& changed, int id, int l, int r) {
    if (x >= r || l >= y) return;
    if (maxi[id] > v)
      potentials[id].push(v);
    if (x <= l && r <= y) {
      while (!potentials[id].empty() && potentials[id].top() > v) {
        changed.insert(potentials[id].top());
        potentials[id].pop();
      }
      upd(id, v);
      return;
    }
    int mid = (l + r) >> 1, il = id + 1, ir = id + (mid - l) * 2;
    push_down(id, il, ir);
    update(x, y, v, changed, il, l, mid);
    update(x, y, v, changed, ir, mid, r);
    maxi[id] = max(maxi[il], maxi[ir]);
  }

  void update(int x, int y, int v, set<int>& changed) {
    changed.clear();
    update(x, y, v, changed, 0, 0, n);
  }

  int get(int x, int y, int id, int l, int r) {
    if (x >= r || l >= y) return -1;
    if (x <= l && r <= y) return maxi[id];
    int mid = (l + r) >> 1, il = id + 1, ir = id + (mid - l) * 2;
    push_down(id, il, ir);
    return max(get(x, y, il, l, mid), get(x, y, ir, mid, r));
  }

  int get(int x, int y) {
    return get(x, y, 0, 0, n);
  }

  int find_left(int x, int v, int id, int l, int r) {
    if (l >= x || maxi[id] < v) return -1;
    if (r-l < 2)
      return l;
    int mid = (l + r) >> 1, il = id + 1, ir = id + (mid - l) * 2;
    push_down(id, il, ir);
    int ret = find_left(x, v, ir, mid, r);
    if (ret < 0)
      ret = find_left(x, v, il, l, mid);
    return ret;
  }

  int find_left(int x, int v) {
    return find_left(x, v, 0, 0, n);
  }
};

SegTree segtree;
map<int, set<pair<int, int>>> queries;
bool answer = true;

void init(int N) {
  segtree.init(N);
  queries.clear();
}

int add_restriction(int L, int R, int X) {
  if (!answer)
    return answer;
  set<int> changed;
  segtree.update(L, R+1, X, changed);
  if (segtree.get(L, R+1) != X) {
    return answer = false;
  }
  auto it = queries[X].lower_bound(make_pair(L, -1));
  if (it == queries[X].end() || it->second > R) {
    if (it != queries[X].end() && it->first <= L && it->second > R) {
      queries[X].erase(it);
    }
    it = queries[X].insert(make_pair(L, R)).first;
    while (it != queries[X].begin()) {
      auto prv = it;
      --prv;
      if (prv->second < R) break;
      queries[X].erase(prv);
    }
  }
  for (int v : changed) {
    int lef = segtree.find_left(L, v) + 1;
    it = queries[v].lower_bound(make_pair(lef, -1));
    if (it != queries[v].end() && segtree.get(it->first, it->second+1) != v) {
      return answer = false;
    }
  }
  return answer;
}
