#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>


using namespace std;
template<class T>
using vec = vector<T>;
using ll = int64_t;

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
    ifstream fin("cycles.in");
    ofstream fout("cycles.out");
    fin.tie(nullptr);
    ll n, m;
    fin >> n >> m;
    vec<ll> X(n);
    for (int i = 0; i < n; ++i) {
        fin >> X[i];
    }
    unordered_set<ll> S;
    for (int i = 0; i < m; ++i) {
        int k;
        fin >> k;
        ll value = 0;
        for (int j = 0; j < k; ++j) {
            ll tmp;
            fin >> tmp;
            value = value | (1 << (tmp - 1));
        }
        S.insert(value);
    }
    ll res = 0;
    int size = 0;
    ll sum = 0;
    for (ll i = 1; i < (1 << n); ++i) {
        bool flag = true;
        for (ll s : S) {
            if ((i & s) == s) {
                flag = false;
                break;
            }
        }
        if (flag) {
            if (size < countOne(i)) {
                size = countOne(i);
                sum = getSum(X, i, n);
            } else if (size == countOne(i)) {
                sum = max(sum, getSum(X, i, n));
            }
        }
    }
    fout << sum << "\n";
    return 0;
}