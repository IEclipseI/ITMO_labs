#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct node {
    node() : min(0), add(0), set(INT64_MAX), left(0), right(0) {
    }

    node(int64_t min, uint32_t left, uint32_t right) : min(min),
                                                       add(0),
                                                       set(INT64_MAX),
                                                       left(left),
                                                       right(right) {
    }

    int64_t min;
    int64_t add;
    int64_t set;
    uint32_t left;
    uint32_t right;

};

node tree[1000000];

void push(uint32_t node) {
    if (tree[node].set == INT64_MAX) {
        tree[2 * node + 1].add += tree[node].add;
        tree[2 * node + 2].add += tree[node].add;
    } else {
        tree[2 * node + 1].add = tree[node].add;
        tree[2 * node + 2].add = tree[node].add;
        tree[2 * node + 1].set = tree[node].set;
        tree[2 * node + 2].set = tree[node].set;
    }
    tree[node].add = 0;
    tree[node].set = INT64_MAX;
}

void set(uint32_t node, uint32_t a, uint32_t b, int64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].set = x;
        tree[node].add = 0;
        return;
    }
    push(node);
    set(2 * node + 1, a, b, x);
    set(2 * node + 2, a, b, x);
    tree[node].min = min((tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : tree[2 * node + 1].set) +
                         tree[2 * node + 1].add,
                         (tree[2 * node + 2].set == INT64_MAX ? tree[2 * node + 2].min : tree[2 * node + 2].set) +
                         tree[2 * node + 2].add);

}

void add(uint32_t node, uint32_t a, uint32_t b, int64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].add += x;
        return;
    }
    push(node);
    add(2 * node + 1, a, b, x);
    add(2 * node + 2, a, b, x);
    tree[node].min = min((tree[2 * node + 1].set == INT64_MAX ? tree[2 * node + 1].min : tree[2 * node + 1].set) +
                         tree[2 * node + 1].add,
                         (tree[2 * node + 2].set == INT64_MAX ? tree[2 * node + 2].min : tree[2 * node + 2].set) +
                         tree[2 * node + 2].add);

}

int64_t minimum(uint32_t node, int64_t a, int64_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return INT64_MAX;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return (tree[node].set == INT64_MAX ? tree[node].min : tree[node].set) + tree[node].add;
    }
    push(node);
    int64_t ans = min(minimum(2 * node + 1, a, b), minimum(2 * node + 2, a, b));
    tree[node].min = min((tree[2 * node + 1].set == INT64_MAX? tree[2 * node + 1].min : tree[2 * node + 1].set) + tree[2 * node + 1].add,
                         (tree[2 * node + 2].set == INT64_MAX? tree[2 * node + 2].min : tree[2 * node + 2].set) + tree[2 * node + 2].add);
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("rmq2.in");
    ofstream fout("rmq2.out");
    uint32_t n;
    fin >> n;
    int64_t size = ceil((double) log((double) n) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t a = length * 2 - 1;
    for (uint32_t i = 0; i < n; ++i) {
        fin >> tree[length - 1 + i].min;
        tree[length - 1 + i].left = i + 1;
        tree[length - 1 + i].right = 1 + i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].min = INT64_MAX;
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].min = min(tree[j * 2 + 1].min, tree[j * 2 + 2].min);
        tree[j].left = tree[2 * j + 1].left;
        tree[j].right = tree[2 * j + 2].right;
    }
    std::string str;
    uint32_t l, r;
    int64_t x;
    while (fin >> str >> l >> r) {
        if (str[0] == 'm') {
            fout << minimum(0, l, r) << '\n';
        } else if (str[0] == 's') {
            fin >> x;
            set(0, l, r, x);
        } else {
            fin >> x;
            add(0, l, r, x);
        }
    }
//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
    fout.close();
    return 0;
}