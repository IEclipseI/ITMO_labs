#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct node {
    node() : min(0), left(0), right(0) {
    }

    node(int64_t min, uint32_t left, uint32_t right) : min(min),
                                                       left(left),
                                                       right(right) {
    }

    int64_t min;
    uint32_t left;
    uint32_t right;

};

node tree[4000000];

void set(uint32_t node, uint32_t a, uint32_t b, int64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].min = x;
        return;
    }
    set(2 * node + 1, a, b, x);
    set(2 * node + 2, a, b, x);
    tree[node].min = min(tree[2 * node + 1].min,
                         tree[2 * node + 2].min);

}


int64_t minimum(uint32_t node, int64_t a, int64_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return INT64_MAX;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return tree[node].min;
    }
    return min(minimum(2 * node + 1, a, b),minimum(2 * node + 2, a, b));
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("parking.in");
    ofstream fout("parking.out");
    uint32_t n, m;
    fin >> n >> m;
    int64_t size = ceil((double) log((double) n) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t a = length * 2 - 1;
    for (uint32_t i = 0; i < n; ++i) {
        tree[length - 1 + i].min = i + 1;
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
    uint32_t l;
    for (int i = 0; i < m; ++i) {
        fin >> str >> l;
        if (str[1] == 'x') {
            set(0, l, l, l);
        } else {
            uint32_t ind = minimum(0, l, n);
            if (ind > n) {
                ind = minimum(0, 0, length);
                fout << ind << "\n";
                set(0, ind, ind, INT64_MAX);
            } else {
                fout << ind << "\n";
                set(0, ind, ind, INT64_MAX);
            };
        }
    }
//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
    fout.close();
    return 0;
}