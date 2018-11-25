#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct node {
    node() : min(0), set(INT64_MIN), left(0), right(0) {
    }

//    node(int64_t min, uint32_t left, uint32_t right) : min(min),
//                                                       set(INT64_MIN),
//                                                       left(left),
//                                                       right(right) {
//    }

    int64_t min;
    int64_t set;
    uint32_t left;
    uint32_t right;

};

node tree[500000];

void push(uint32_t node) {
    if (tree[node].set != INT64_MIN) {
        tree[2 * node + 1].set = max(tree[node].set, tree[2 * node + 1].set);
        tree[2 * node + 2].set = max(tree[node].set, tree[2 * node + 2].set);
    }
    tree[node].set = INT64_MIN;
}

void set(uint32_t node, uint32_t a, uint32_t b, int64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].set = max(x, tree[node].set);
        return;
    }
    push(node);
    set(2 * node + 1, a, b, x);
    set(2 * node + 2, a, b, x);
}


int64_t minimum(uint32_t node, int64_t a, int64_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return INT32_MAX;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return tree[node].min;
    }
    return min(minimum(2 * node + 1, a, b), minimum(2 * node + 2, a, b));
}


int main() {
    ios::sync_with_stdio(false);
//    ofstream f("rmq.in");
//    f << 100000 << " " << 100000 << endl;
//    for (int i = 0; i < 100000; ++i) {
//        f << 1 << " " << 1+i << " " << 100000 - i << endl;
//    }
//    f.close();
    ifstream fin("rmq.in");
    ofstream fout("rmq.out");
    uint32_t n, m;
    fin >> n >> m;
    int64_t size = ceil((double) log((double) n) / log((double) 2));
    uint32_t length = pow(2, size);
    for (uint32_t i = 0; i < n; ++i) {
        tree[length - 1 + i].left = i + 1;
        tree[length - 1 + i].right = 1 + i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].min = INT32_MAX;
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].min = min(tree[j * 2 + 1].min, tree[j * 2 + 2].min);
        tree[j].left = tree[2 * j + 1].left;
        tree[j].right = tree[2 * j + 2].right;
    }
    uint32_t l, r;
    int32_t x;
    int32_t *quest = new int32_t[300000];
    for (int i = 3 * m; i >= 0; --i) {
        quest[i] = 0;
    }
    for (int32_t i = 0; i < m; ++i) {
        fin >> l >> r >> x;
        quest[3 * i] = l;
        quest[3 * i + 1] = r;
        quest[3 * i + 2] = x;
        set(0, l, r, x);
    }
    for (uint32_t i = 0; i < length - 1; ++i) {
        push(i);
    }
    for (int i = 0; i < n; ++i) {
        tree[length - 1 + i].min = tree[length - 1 + i].set == INT64_MIN ? INT32_MAX : tree[length - 1 + i].set;
    }

    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].min = min(tree[j * 2 + 1].min, tree[j * 2 + 2].min);
    }
    for (int i = 0; i < m; ++i) {
        if (minimum(0, quest[3*i], quest[3*i + 1]) != quest[3*i+ 2]) {
            fout << "inconsistent" << endl;
            fout.close();
            return 0;
        }
    }
    fout << "consistent" << endl;
    for (int i = 0; i < n; ++i) {
        fout << tree[length - 1 + i].min << " ";
    }


//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
    fout.close();
    return 0;
}