#include <iostream>
#include <vector>
#include <cmath>

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
            z[i] = min(r-i+1, static_cast<const int &>(z[i - l]));
        while (i+z[i] < s.size() && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string p, t;
    cin >> p >> t;
    string pt = p + "|" + t;
    auto z = z_function(pt);
    int count = 0;
    for (int i = p.size() + 1; i < pt.size(); ++i) {
        if (z[i] == p.size())
            count++;
    }
    cout << count << "\n";
    for (int i = p.size() + 1; i < pt.size(); ++i) {
        if (z[i] == p.size())
            cout << i - p.size() << " ";
    }
    return 0;
}