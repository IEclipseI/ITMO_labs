#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;
template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint64_t;

vec<ui> prefix_f(const string &s) {
    vec<ui> pref(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        ui j = pref[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pref[j - 1];
        }
        if (s[i] == s[j])
            ++j;
        pref[i] = j;
    }
    return pref;
}

vec<ui> z_function(const string &s) {
    vec<ui> z(s.size(), 0);
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, static_cast<const int &>(z[i - l]));
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vec<ui> p_pow;
vec<ui> h_pow;
ui p = 7;
ui h = 11;

struct hash_f {
    int operator()(const pair<ui, ui> &a) const {
        return static_cast<int>(31 * a.first + a.second);
    }
};

unordered_map<pair<ui, ui>, int, hash_f> string_hashes(const string &s, ui len) {
    vec<pair<pair<ui, ui>, int>> hashes(s.size() - len + 1, make_pair(make_pair(0, 0), 0));
    for (int i = 0; i < len; ++i) {
        hashes[0].first.first = hashes[0].first.first * p + (s[i] - 'a' + 1);
        hashes[0].first.second = hashes[0].first.second * h + (s[i] - 'a' + 1);
    }
    for (int i = 1; i <= s.size() - len; ++i) {
        hashes[i].first.first =
                (hashes[i - 1].first.first - (s[i - 1] - 'a' + 1) * p_pow[len - 1]) * p + (s[i + len - 1] - 'a' + 1);
        hashes[i].first.second =
                (hashes[i - 1].first.second - (s[i - 1] - 'a' + 1) * h_pow[len - 1]) * h + (s[i + len - 1] - 'a' + 1);
        hashes[i].second = i;
    }
    unordered_map<pair<ui, ui>, int, hash_f> res;
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

vec<int> pos;

bool f(string &s, string &t, ll len) {
    auto s_hash = string_hashes(s, static_cast<ui>(len));
    auto t_hash = string_hashes(t, static_cast<ui>(len));
    bool answer = false;
    for (auto tt: t_hash) {
        if (s_hash.find(tt.first) != s_hash.end()) {
            if (!answer && max_len < len) {
                pos.clear();
                max_len = len;
            }
            if (len == max_len) {
                pos.push_back(tt.second);
                answer = true;
            }
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("common.in");
    ofstream fout("common.out");
    string s, t;
    fin >> s >> t;
    if (s.length() < t.length())
        swap(s, t);
    fill_pow(s.length());

    ll l = -1, r = t.size() + 1;
    while (l < r - 1) {
        ll m = (r + l) / 2;
        if (f(s, t, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (pos.size() > 0) {
        string answer = t.substr(pos[0], r - 1);
        for (int i = 1; i < pos.size(); ++i) {
            answer = min(answer, t.substr(pos[i], r - 1));
        }
        fout << answer << "\n";
    }

//    string_view view;
//    fout << t.substr(ind, r - 1)<< "\n";


    return 0;
}