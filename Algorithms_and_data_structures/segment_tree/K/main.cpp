//
// Created by Роман on 21.04.2018.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct node {
    node() : sum(0), hashSum(0), left(0), right(0) {
    }
    uint64_t sum;
    uint64_t hashSum;
    uint32_t left;
    uint32_t right;

};

node tree[400000];
uint64_t hashes[100000];
uint64_t prefHashes[100000];
uint64_t prefSum[100000];

void set(uint32_t node, uint32_t a, uint32_t b, uint64_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].sum = x;
        tree[node].hashSum = hashes[x - 1];
        return;
    }
    set(2 * node + 1, a, b, x);
    set(2 * node + 2, a, b, x);
    tree[node].sum = tree[2 * node + 1].sum + tree[2 * node + 2].sum;
    tree[node].hashSum = tree[2 * node + 1].hashSum + tree[2 * node + 2].hashSum;
}

pair<uint64_t,uint64_t> summary(uint32_t node, int64_t a, int64_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return pair<uint64_t, uint64_t>(0, 0);
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return pair<uint64_t, uint64_t>(tree[node].sum, tree[node].hashSum);
    }
    pair<uint64_t, uint64_t> l(summary(2 * node + 1, a, b));
    pair<uint64_t, uint64_t> r(summary(2 * node + 2, a, b));
    pair<uint64_t, uint64_t> ans(l.first + r.first, l.second + r.second);
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("permutation.in");
    ofstream fout("permutation.out");
    uint32_t n;
    fin >> n;
    prefSum[0] = 1;
    hashes[0] = 11;
    prefHashes[0] = 11;
    for (int i = 1; i < n; ++i) {
        prefSum[i] = prefSum[i - 1] + i + 1;
        hashes[i] = hashes[i - 1] * 11;
        prefHashes[i] = hashes[i] + prefHashes[i - 1];
    }

    int64_t size = ceil((double) log((double) n) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t a = length * 2 - 1;
    for (uint32_t i = 0; i < n; ++i) {
        fin >> tree[length - 1 + i].sum;
        tree[length - 1 + i].hashSum = hashes[tree[length - 1 + i].sum - 1];
        tree[length - 1 + i].left = i + 1;
        tree[length - 1 + i].right = 1 + i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].sum = tree[j * 2 + 1].sum + tree[j * 2 + 2].sum;
        tree[j].hashSum = tree[j * 2 + 1].hashSum + tree[j * 2 + 2].hashSum;
        tree[j].left = tree[2 * j + 1].left;
        tree[j].right = tree[2 * j + 2].right;
    }
    uint32_t m;
    fin>>m;
    uint32_t X, Y;
    int t;
    for (int i = 0; i < m; ++i) {
        fin >> t >> X >> Y;
        if (t == 1) {
            set(0, X, X , Y);
        } else {
            pair<uint64_t, uint64_t> ans(summary(0, X, Y));
            if (ans.first == prefSum[Y - X] && ans.second == prefHashes[Y - X]) {
                fout <<"YES" << endl;
            } else {
                fout << "NO" << endl;
            }
        }
    }
    fout.close();
    return 0;
}
