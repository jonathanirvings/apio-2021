#include "height.h"

#include <algorithm>
#include <map>
#include <queue>
#include <set>

const int INF = 1000000005;

class SegTree {
  struct Node {
    std::priority_queue<int> vals;
    int lazy;

    Node() {
      vals.push(INF);
      lazy = -1;
    }

    std::vector<int> update(int x) {
      if (vals.top() <= x) return {};
      std::vector<int> updated;
      while (!vals.empty() && vals.top() > x) {
        updated.push_back(vals.top());
        vals.pop();
      }
      if (vals.empty() || vals.top() != x) {
        vals.push(x);
      }

      if (lazy == -1 || lazy > x) lazy = x;
      return updated;
    }

    void insert(int x) {
      if (vals.top() > x) vals.push(x);
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
    Node &lchild = nodes[idx*2 + 1], &rchild = nodes[idx*2 + 2];
    if (lchild.vals.empty() || rchild.vals.empty()) return;
    nodes[idx].update(std::max(lchild.vals.top(), rchild.vals.top()));
  }

  void update(int idx, int l, int r, int ll, int rr, int val, std::vector<int> &updated) {
    if (r <= ll || l >= rr) return;
    if (l >= ll && r <= rr) {
      for (int u : nodes[idx].update(val)) {
        updated.push_back(u);
      }
      return;
    }

    nodes[idx].insert(val);
    push_down(idx);
    int mid = (l + r) / 2;

    update(idx*2 + 1, l, mid, ll, rr, val, updated);
    update(idx*2 + 2, mid, r, ll, rr, val, updated);
    pull_up(idx);
  }

  int query(int idx, int l, int r, int ll, int rr) {
    if (r <= ll || l >= rr) return 0;
    if (l >= ll && r <= rr) return nodes[idx].vals.top();

    push_down(idx);

    int mid = (l + r) / 2;
    return std::max(query(idx*2 + 1, l, mid, ll, rr),
                    query(idx*2 + 2, mid, r, ll, rr));
  }

 public:
  void build(int _n) {
    n = _n;
    nodes.assign(n * 4, Node());
  }

  std::vector<int> update(int l, int r, int x) {
    std::vector<int> updated;
    update(0, 0, n, l, r, x, updated);
    std::sort(updated.begin(), updated.end());
    updated.erase(std::unique(updated.begin(), updated.end()), updated.end());
    return updated;
  }

  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }
} tree;

int answer;
std::map<int, std::set<std::pair<int, int>>> queries;

void init(int N) {
  tree.build(N);
  answer = 1;
  queries.clear();
}

int add_restriction(int L, int R, int X) {
  ++R;
  if (answer == 0) return 0;

  {
    std::set<std::pair<int, int>> &ranges = queries[X];
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
    }
  }

  for (int updated : tree.update(L, R, X)) {
    std::set<std::pair<int, int>> &ranges = queries[updated];
    auto it = ranges.lower_bound({L, -1});
    if (it != ranges.end() && tree.query(it->first, it->second) != updated) {
      return answer = 0;
    }
    if (it != ranges.begin()) {
      auto prv = std::prev(it);
      if (tree.query(prv->first, prv->second) != updated) {
        return answer = 0;
      }
    }
  }

  if (tree.query(L, R) != X) return answer = 0;
  return 1;
}
