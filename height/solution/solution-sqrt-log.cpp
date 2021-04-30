#include "height.h"

#include <cmath>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>

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

  int get_pos(int idx, int l, int r, int ll, int rr, int val) {
    if (r <= ll || l >= rr || nodes[idx].maxi < val) return -1;
    if (l + 1 == r) return l;

    push_down(idx);

    int mid = (l + r) / 2;
    int get_r = get_pos(idx*2 + 2, mid, r, ll, rr, val);
    if (get_r != -1) return get_r;
    return get_pos(idx*2 + 1, l, mid, ll, rr, val);
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

  int get_pos(int l, int r, int val) {
    return get_pos(0, 0, n, l, r, val);
  }
} tree;

class Buckets {
  int n;
  int block_size;
  std::vector<std::priority_queue<int>> blocks;
  std::vector<int> values;

 public:
  void build(int _n) {
    n = _n;
    block_size = sqrt(n);
    blocks.assign((n + block_size - 1) / block_size, std::priority_queue<int>());
    values.assign(n, INF);
  }

  std::vector<int> update(int l, int r, int x) {
    --r;
    std::vector<int> updated;

    int block_l = l / block_size, block_r = r / block_size;
    if (block_l == block_r) {
      if (blocks[block_l].empty() || blocks[block_l].top() != x) {
        blocks[block_l].push(x);
      }
      for (int i = l; i <= r; ++i) {
        if (values[i] > x) {
          updated.push_back(values[i]);
          values[i] = x;
        }
      }
    } else {
      if (blocks[block_l].empty() || blocks[block_l].top() != x) {
        blocks[block_l].push(x);
      }
      for (int i = l; i / block_size == block_l; ++i) {
        if (values[i] > x) {
          updated.push_back(values[i]);
          values[i] = x;
        }
      }

      if (blocks[block_r].empty() || blocks[block_r].top() != x) {
        blocks[block_r].push(x);
      }
      for (int i = r; i / block_size == block_r; --i) {
        if (values[i] > x) {
          updated.push_back(values[i]);
          values[i] = x;
        }
      }
      for (int i = block_l + 1; i < block_r; ++i) {
        while (!blocks[i].empty() && blocks[i].top() > x) {
          updated.push_back(blocks[i].top());
          blocks[i].pop();
        }
        if (blocks[i].empty() || blocks[i].top() != x) {
          blocks[i].push(x);
        }
      }
    }

    std::sort(updated.begin(), updated.end());
    updated.erase(std::unique(updated.begin(), updated.end()), updated.end());
    return updated;
  }
} buckets;

int answer;
std::map<int, std::set<std::pair<int, int>>> queries;

void init(int N) {
  tree.build(N);
  buckets.build(N);
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
      auto nxt = std::next(it);
      if (nxt != ranges.end() && nxt->first <= L) {
        ranges.erase(nxt);
      }
    }
  }

  tree.update(L, R, X);

  for (int updated : buckets.update(L, R, X)) {
    std::set<std::pair<int, int>> &ranges = queries[updated];
    auto it = ranges.lower_bound({tree.get_pos(0, L, updated) + 1, -1});
    if (it != ranges.end() && tree.query(it->first, it->second) != updated) {
      return answer = 0;
    }
  }

  if (tree.query(L, R) != X) return answer = 0;
  return 1;
}
