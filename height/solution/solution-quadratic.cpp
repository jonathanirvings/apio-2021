#include "height.h"

#include <algorithm>
#include <vector>

const int INF = 1000000005;

class SegTree {
  struct Node {
    int maxi, lazy;
    Node(int _maxi): maxi(_maxi), lazy(-1) {}

    void update(int val) {
      if (val < maxi) {
        maxi = lazy = val;
      }
    }
  };

  int n;
  std::vector<Node> nodes;

  void push_down(int idx) {
    int &lazy = nodes[idx].lazy;
    if (lazy == -1) return;
    nodes[idx*2 + 1].update(lazy);
    nodes[idx*2 + 2].update(lazy);
    lazy = -1;
  }

  void pull_up(int idx) {
    nodes[idx].maxi = std::max(
      nodes[idx*2 + 1].maxi, nodes[idx*2 + 2].maxi
    );
  }

  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (r <= ll || l >= rr) return;
    if (l >= ll && r <= rr) return nodes[idx].update(val);

    push_down(idx);
    int mid = (l + r) / 2;

    update(idx*2 + 1, l, mid, ll, rr, val);
    update(idx*2 + 2, mid, r, ll, rr, val);
    pull_up(idx);
  }
 
  int query(int idx, int l, int r, int ll, int rr) {
    if (r <= ll || l >= rr) return 0;
    if (l >= ll && r <= rr) return nodes[idx].maxi;

    push_down(idx);

    int mid = (l + r) / 2;
    return std::max(query(idx*2 + 1, l, mid, ll, rr),
                    query(idx*2 + 2, mid, r, ll, rr));
  }

 public:
  void build(int _n) {
    n = _n;
    nodes.assign(n * 4, Node(INF));
  }

  void update(int l, int r, int x) {
    update(0, 0, n, l, r, x);
  }

  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }
} tree;

int answer;
std::vector<std::tuple<int, int, int>> queries;

void init(int N) {
  tree.build(N);
  answer = 1;
  queries.clear();
}

int add_restriction(int L, int R, int X) {
  ++R;
  if (answer == 0) return 0;

  tree.update(L, R, X);

  queries.emplace_back(L, R, X);
  for (auto [l, r, x] : queries) {
    if (tree.query(l, r) != x) {
      return answer = 0;
    }
  }

  return 1;
}
