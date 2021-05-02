#include "height.h"

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int INF = 2e9 + 5;

int NN;
bool can = true;
map<int, set<pair<int, int> > > queries;

struct node {
    int max, smax, lazy;

    bool update(int val){
        // Update minimum
        if (smax < val && val < max) {
            max = lazy = val;
            return true;
        }

        return false;
    }
};

node st[4 * MAXN];
set<int> check_list;

node merge(node a, node b){
    if(a.max == b.max)return {a.max, max(a.smax, b.smax), 0};
    if(a.max > b.max)return {a.max, max(a.smax, b.max), 0};
    return {b.max, max(a.max, b.smax), 0};
}

void init_segtree(int idx, int l, int r){
    if(l == r){
        st[idx] = {INF, -INF, 0};
        return;
    }

    int m = (l + r) / 2;
    init_segtree(idx * 2, l, m);
    init_segtree(idx * 2 + 1, m + 1, r);

    st[idx] = merge(st[idx * 2], st[idx * 2 + 1]);
}

void propagate(int idx){
    if(st[idx].lazy == 0)return;
    st[idx * 2].update(st[idx].lazy);
    st[idx * 2 + 1].update(st[idx].lazy);
    st[idx].lazy = 0;
}

void update(int idx, int l, int r, int L, int R, int val){
    if(l > R || r < L || st[idx].max <= val)return;
    if(l >= L && r <= R){
        int cur_max = st[idx].max;
        if(st[idx].update(val)){
            check_list.insert(cur_max);
            return;
        }
        // Condition for beats not fulfilled, split recursively
    }

    propagate(idx);
    int m = (l + r) / 2;

    update(idx * 2    , l,     m, L, R, val);
    update(idx * 2 + 1, m + 1, r, L, R, val);

    st[idx] = merge(st[idx * 2], st[idx * 2 + 1]);
}

int get(int idx, int l, int r, int L, int R){
    if(l > R || r < L) return 0;
    if(l >= L && r <= R) return st[idx].max;
    propagate(idx);

    int m = (l + r) / 2;

    return max(get(idx * 2    , l,     m, L, R),
               get(idx * 2 + 1, m + 1, r, L, R));
}

int first_larger_equal_val(int idx, int l, int r, int L, int R, int val){
    if(l > R || r < L || st[idx].max < val)return -1;
    if(l == r)return l;

    propagate(idx);

    int m = (l + r) / 2;
    
    int rgt = first_larger_equal_val(idx * 2 + 1, m + 1, r, L, R, val);
    if (rgt != -1) return rgt;

    return first_larger_equal_val(idx * 2, l, m, L, R, val);
}

void init(int N) {
    NN = N - 1;
    queries.clear();
    init_segtree(1, 0, N);
}

void insert_new_range(int L, int R, int X) {
    set<pair<int, int> > &ranges = queries[X];

    auto it = ranges.lower_bound({L, -1});

    if (it == ranges.end() || it->second > R){
        // New range is not wrapped
        it = ranges.insert({L, R}).first;
        
        // Check whether prev wraps current query
        while(it != ranges.begin() && prev(it)->second >= R){
            ranges.erase(prev(it));
        }
    }
}

int add_restriction(int L, int R, int X) {
    if(!can)return can;
    
    insert_new_range(L, R, X);
    check_list.clear();

    update(1, 0, NN, L, R, X);

    for(int V: check_list) {
        set<pair<int, int> > &ranges = queries[V];

        int most_right = first_larger_equal_val(1, 0, NN, 0, L - 1, V);
        auto it = ranges.lower_bound({most_right + 1, -1});
        
        if (it != ranges.end() && get(1, 0, NN, it->first, it->second) != V){
            return can = false;
        }
    }

    int val = get(1, 0, NN, L, R);
    return can = (val == X);
}
