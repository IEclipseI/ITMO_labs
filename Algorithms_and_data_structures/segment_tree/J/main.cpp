#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;


struct node {
    node() : min(0), set(INT64_MAX), left(0), right(0) {
    }

    node(int64_t min, uint32_t left, uint32_t right) : min(min),
                                                       set(INT64_MAX),
                                                       left(left),
                                                       right(right) {
    }

    int64_t min;
    int64_t set;
    uint32_t left;
    uint32_t right;

};

node tree[5000000];

void push(uint32_t node) {
    if (tree[node].set != INT64_MAX) {
        tree[2 * node + 1].set = tree[2 * node + 1].set == INT64_MAX ? tree[node].set : max(tree[node].set, tree[2 * node + 1].set);
        tree[2 * node + 2].set = tree[2 * node + 2].set == INT64_MAX ? tree[node].set : max(tree[node].set, tree[2 * node + 2].set);
        tree[node].set = INT64_MAX;
    }
}

void set(uint32_t node, uint32_t a, uint32_t b, int64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].set = tree[node].set == INT64_MAX ? x : max(x, tree[node].set);
        return;
    }
    push(node);
    set(2 * node + 1, a, b, x);
    set(2 * node + 2, a, b, x);
    tree[node].min = min((tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : max(tree[2 * node + 1].set,
                                                                                             tree[2 * node + 1].min)),
                         (tree[2 * node + 2].set == INT64_MAX ? tree[2 * node + 2].min : max(tree[2 * node + 2].set,
                                                                                             tree[2 * node + 2].min)));

}

uint32_t search_min(uint32_t node, int64_t min) {
    if (tree[node].left == tree[node].right) {
        return tree[node].left;
    }
    push(node);
    uint32_t ans;
    int64_t l = tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : max(tree[2 * node + 1].set,
                                                                                   tree[2 * node + 1].min);
    if (l == min) {
        ans = search_min(2 * node + 1, min);
    } else {
        ans = search_min(2 * node + 2, min);
    }
    tree[node].min = std::min(
            (tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : max(tree[2 * node + 1].set,
                                                                                tree[2 * node + 1].min)),
            (tree[2 * node + 2].set == INT64_MAX ? tree[2 * node + 2].min : max(tree[2 * node + 2].set,
                                                                                tree[2 * node + 2].min)));

    return ans;
}

pair<uint32_t, int64_t> minimum(uint32_t node, int64_t a, int64_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return pair<uint32_t, int64_t>(UINT32_MAX, INT64_MAX);
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        int64_t ans = tree[node].set == INT64_MAX ? tree[node].min : max(tree[node].set, tree[node].min);
        uint32_t min_ind = search_min(node, ans);
        return pair<uint32_t, int64_t>(min_ind, ans);
    }
    push(node);
    pair<uint32_t, int64_t> l(minimum(2 * node + 1, a, b));
    pair<uint32_t, int64_t> r(minimum(2 * node + 2, a, b));
    uint32_t min_ind = l.second > r.second ? r.first : l.first;
    pair<uint32_t, int64_t> ans = pair<uint32_t, int64_t>(min_ind, min(l.second, r.second));
    tree[node].min = min((tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : max(tree[2 * node + 1].set,
                                                                                             tree[2 * node + 1].min)),
                         (tree[2 * node + 2].set == INT64_MAX ? tree[2 * node + 2].min : max(tree[2 * node + 2].set,
                                                                                             tree[2 * node + 2].min)));
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    uint32_t n;
    uint32_t m;
    cin >> n >> m;
    int64_t size = static_cast<int64_t>(ceil((double) log((double) n) / log((double) 2)));
    uint32_t length = static_cast<uint32_t>(pow(2, size));
    for (uint32_t i = 0; i < n; ++i) {
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].min = INT64_MAX;
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].left = tree[2 * j + 1].left;
        tree[j].right = tree[2 * j + 2].right;
    }
    std::string str;
    uint32_t l, r;
    int64_t x;
    for (int i = 0; i < m; ++i) {
        cin >> str >> l >> r;
        if (str[0] == 'd') {
            cin >> x;
            set(0, l, r, x);
        } else {
            pair<uint32_t, int64_t> p = minimum(0, l, r);
            cout << p.second << " " << p.first << endl;
        }
    }
//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
    return 0;
}