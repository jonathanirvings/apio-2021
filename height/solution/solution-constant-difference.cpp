#include "height.h"

#include <algorithm>
#include <map>
#include <set>
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
std::set<std::pair<int, int>> ranges;
std::map<std::pair<int, int>, int> queries;

void init(int N) {
  tree.build(N);
  answer = 1;
  ranges.clear();
  queries.clear();
}

int add_restriction(int L, int R, int X) {
  ++R;
  if (answer == 0) return 0;

  // optional step that removes redundant queries
  {
    auto it = ranges.lower_bound({L, -1});
    if (it == ranges.end() || it->second > R) {
      it = ranges.insert({L, R}).first;
      while (it != ranges.begin()) {
        auto prv = std::prev(it);
        if (prv->second >= R) {
          ranges.erase(prv);
        } else {
          break;
        }
      }
      auto nxt = std::next(it);
      if (nxt != ranges.end() && nxt->first <= L) {
        ranges.erase(nxt);
      }
    }
  }

  if (queries.find({L, R}) != queries.end() && queries[{L, R}] != X) {
    return answer = 0;
  }
  tree.update(L, R, X);
  queries[{L, R}] = X;

  {
    auto it = ranges.lower_bound({L + 1, -1});
    if (it != ranges.end() && tree.query(it->first, it->second) != queries[*it]) {
      return answer = 0;
    }
    it = ranges.lower_bound({L, -1});
    if (it != ranges.begin()) {
      auto prv = std::prev(it);
      if (tree.query(prv->first, prv->second) != queries[*prv]) {
        return answer = 0;
      }
    }
  }

  if (tree.query(L, R) != X) return answer = 0;
  return 1;
}
