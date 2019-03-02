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
    ifstream fin("check.in");
    ofstream fout("check.out");
//    for (int l = 0; l < 1000; ++l) {
    fin.tie(nullptr);
    ll n, m;
    fin >> n >> m;
    unordered_set<ll> S;
    for (int i = 0; i < m; ++i) {
        int k;
        fin >> k;
        ll value = 0;
        set<ll> hz;
        for (int j = 0; j < k; ++j) {
            ll tmp;
            fin >> tmp;
            hz.insert(tmp);
            value = value | (1 << (tmp - 1));
        }
        if (hz.size() != k)
            throw 3;
        S.insert(value);
    }
    bool has_0 = true;
    bool has_every = true;
    bool incr = true;
    if (S.find(0) == S.end())
        has_0 = false;
    for (ll t : S) {
        for (ll i = 1; i < t; ++i) {
            if ((t | i) <= t)
                if (S.find(i) == S.end())
                    has_every = false;
        }
    }
    int a = 0;
    for (ll t1 : S) {
        for (ll s1 : S) {
            ll t = t1;
            ll s = s1;
            if (countOne(t) != countOne(s)) {
                if (countOne(t) > countOne(s)) {
                    swap(t, s);
                }
                bool test = false;
                ll copy_t = t;
                copy_t = t ^ (s | t);
                for (int i = 0; i < n; ++i) {
                    if (((copy_t & (1 << i))) != 0) {
                        if (S.find(t | (copy_t & (1 << i))) != S.end())
                            test = true;
                    }
                }
                incr = incr && test;
            }
        }
    }
    if (has_0 && has_every && incr) {
        fout << "YES\n";
    } else {
        fout << "NO\n";
    }
//        cout << a;
    return 0;
}