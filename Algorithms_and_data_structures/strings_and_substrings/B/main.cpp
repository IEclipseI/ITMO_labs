#include <iostream>
#include <vector>

using namespace std;

template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint64_t ;


vec<ui>  prefix_f(const string& s) {
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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    vec<ui> pref = prefix_f(s);
    for (int i = 0; i < s.size(); ++i) {
        cout << pref[i] << " ";
    }
    return 0;
}