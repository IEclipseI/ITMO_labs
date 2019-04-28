#include <iostream>
#include <vector>

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


vec<ui> p_pow;
vec<ui> h_pow;
ui p = 7;
ui h = 11;

vec<pair<ui, ui>> string_hashes(const string &s) {
    vec<pair<ui, ui>> hashes(s.size() + 1, make_pair(0, 0));
    hashes[1].first = s[0];
    hashes[1].second = s[0];
    for (int i = 1; i <= s.size(); ++i) {
        hashes[i].first = hashes[i - 1].first + p_pow[i - 1] * (s[i - 1] - 'a' + 1);
        hashes[i].second = hashes[i - 1].second + h_pow[i - 1] * (s[i - 1] - 'a' + 1);
    }
    return hashes;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    fill_pow(s.size());
    vec<pair<ui, ui>> hashes = string_hashes(s);

    ui m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        ui a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        if (a2 - a1 != b2 - b1) {
            cout << "No\n";
        } else {
            if (b2 < a2) {
                swap(b2, a2);
                swap(b1, a1);
            }
            ui hash_b_p = hashes[b2].first - hashes[b1 - 1].first;
            ui hash_b_h = hashes[b2].second - hashes[b1 - 1].second;
            ui hash_a_p = hashes[a2].first - hashes[a1 - 1].first;
            ui hash_a_h = hashes[a2].second - hashes[a1 - 1].second;
            if (hash_b_p == hash_a_p * p_pow[(b1 - a1)]
                && hash_b_h == hash_a_h * h_pow[(b1 - a1)]) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}