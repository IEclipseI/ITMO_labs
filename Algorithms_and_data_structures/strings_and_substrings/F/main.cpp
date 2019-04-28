#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;
template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint64_t;


vec<ui> p_pow;
vec<ui> h_pow;
ui p = 31;
ui h = 11;

struct hash_f {
    int operator()(const pair<ui, ui> &a) const {
        return static_cast<int>(31 * a.first + a.second);
    }
};

unordered_map<ui, int> string_hashes(const string &s, ui len) {
    vec<pair<ui, int>> hashes(s.size() - len + 1, {0,0});
    for (int i = 0; i < len; ++i) {
        hashes[0].first = hashes[0].first * p + (s[i] - 'a' + 1);
    }
    for (int i = 1; i <= s.size() - len; ++i) {
        hashes[i].first =
                (hashes[i - 1].first - (s[i - 1] - 'a' + 1) * p_pow[len - 1]) * p + (s[i + len - 1] - 'a' + 1);
        hashes[i].second = i;
    }
    unordered_map<ui, int> res;
    res.insert(hashes.begin(), hashes.end());
    return res;
}

void fill_pow(ui n) {
    p_pow.resize(n + 1, 0);
    p_pow[0] = 1;
    h_pow.resize(n + 1, 0);
    h_pow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p_pow[i] = p_pow[i - 1] * p;
        h_pow[i] = h_pow[i - 1] * h;
    }
}

int max_len = 0;

unordered_map<ui, int> pos;

bool f(vec<string> strs, ll len) {
    bool answer = false;
    auto first = string_hashes(strs[0], len);
    for (int i = 1; i < strs.size(); ++i) {
        unordered_map<ui, int> tmp;
        auto cur = string_hashes(strs[i], len);
        for (auto p : cur) {
            auto it = first.find(p.first);
            if (it != first.end())
                tmp.insert(*it);
        }
        swap(first, tmp);
    }
    if (!first.empty() && len > max_len) {
        max_len = len;
        pos = first;
    }
    return !first.empty();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vec<string> strings;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string tmp;
        cin >> tmp;
        strings.push_back(tmp);
    }
    sort(strings.begin(), strings.end(), [](const string& a,const string& b){ return a.size() < b.size();});
    fill_pow(strings.back().length());

    ll l = -1, r = strings[0].size() + 1;
    while (l < r - 1) {
        ll m = (r + l) / 2;
        if (f(strings, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (pos.size() > 0)
        cout << strings[0].substr(pos.begin()->second, max_len)<< "\n";
    else
        cout << "\n";

    return 0;
}