#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>


using namespace std;
template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint32_t;

vec<bool> used;
vec<vec<ui>> G;
vec<ui> order;
vec<int> match_right;
vec<int> match_left;
vec<ll> w;

bool kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (ui to : G[v]) {
        if (match_right[to] == -1 || kuhn(match_right[to])) {
            match_right[to] = v;
            match_left[v] = to;
            return true;
        }
    }
    return false;
}

int countOne(ll x) {
    int res = 0;
    while (x > 0) {
        res += (x & 1);
        x >>= 1;
    }
    return res;
}

ll getSum(vec<ll> &X, ll i, ll n) {
    ll sum = 0;
    for (int j = 0; j < n; ++j) {
        if (((i >> j) & 1) == 1) {
            sum += X[j];
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("matching.in");
    ofstream fout("matching.out");
//    for (int l = 0; l < 1000; ++l) {
    fin.tie(nullptr);
    ui n;
    fin >> n;
    w.resize(n, -1);
    G.resize(n);
    order.resize(n);
    used.resize(n);
    match_right.resize(n, -1);
    match_left.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        fin >> w[i];
        order[i] = static_cast<unsigned int>(i);
    }
    for (ui i = 0; i < n; ++i) {
        int k;
        fin >> k;
        for (ui j = 0; j < k; ++j) {
            ui v;
            fin >> v;
            G[i].push_back(v - 1);
//            G[v].push_back(i);
        }
    }
    sort(order.begin(), order.end(), [](const ui &a, const ui &b) { return w[a] >= w[b]; });

    for (int i = 0; i < n; ++i) {
        ui v = order[i];
        used.assign(n, false);
        kuhn(v);
    }
    for (int l = 0; l < match_right.size(); ++l) {
        fout << match_left[l] + 1 << "\n";
    }
    return 0;
}