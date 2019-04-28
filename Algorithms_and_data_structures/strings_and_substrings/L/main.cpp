#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint64_t;

std::vector<std::vector<int64_t>> cs;

std::vector<int64_t> suf_array(string s) {
//    s.push_back(0);
    int n = s.length();
    std::vector<int64_t> c(n);
    std::vector<int64_t> pre(n);
    for (int i = 0; i < n; ++i) {
        pre[i] = i;
    }
    std::sort(pre.begin(), pre.end(), [&s](int64_t a, int64_t b) { return s[a] < s[b]; });
    c[pre[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[pre[i]] != s[pre[i - 1]])
            c[pre[i]] = c[pre[i - 1]] + 1;
        else
            c[pre[i]] = c[pre[i - 1]];
    }
    int m = static_cast<int>(ceil(log2(n)));
    cs.push_back(c);
    for (int i = 1; i <= m; ++i) {
        int len = std::min(static_cast<int>(pow(2, i - 1)), n);
        std::sort(pre.begin(), pre.end(),
                  [&c, len, n](int64_t a, int64_t b) {
                      if (c[a] != c[b])
                          return c[a] < c[b];
                      else {
                          return c[(a + len) % n] < c[(b + len) % n];
                      }
                  });
        std::vector<int64_t> new_c(n);
        new_c[pre[0]] = 0;
        for (int j = 1; j < n; ++j) {
            if (c[pre[j]] != c[pre[j - 1]])
                new_c[pre[j]] = new_c[pre[j - 1]] + 1;
            else if (c[(pre[j] + len) % n] != c[(pre[j - 1] + len) % n])
                new_c[pre[j]] = new_c[pre[j - 1]] + 1;
            else
                new_c[pre[j]] = new_c[pre[j - 1]];
        }
        std::swap(c, new_c);
        cs.push_back(c);
    }
    return pre;
}

int lcp(string &s, int i, int j) {
    int ans = 0;
    for (int k = static_cast<int>(ceil(static_cast<double>(log2(s.length())))); k >= 0; --k) {
        if (cs[k][i] == cs[k][j]) {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
        if (i > s.size() || j > s.size())
            return ans;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
//    cin.tie(nuint64_tptr);
    ifstream fin("shifts.in");
    ofstream fout("shifts.out");
    string s;
    getline(fin, s);
    std::vector<int64_t> suf_ar = suf_array(s);
    vec<ll> f;
    f.push_back(suf_ar[0]);
//    for (int i = 0; i < suf_ar.size(); ++i) {
//        fout << suf_ar[i] << " ";
//    }
//    fout << "\n";
    for (int i = 1; i < suf_ar.size(); ++i) {
        if (lcp(s, suf_ar[i - 1], suf_ar[i]) < s.length()) {
//            fout << lcp(s, suf_ar[i - 1], suf_ar[i])  << " ";
            f.push_back(suf_ar[i]);
        }
    }
//    fout << "\n";
//    for (int i = 0; i < f.size(); ++i) {
//        fout << f[i] << " ";
//    }
    s = s + s;
    int k;
    fin >> k;
    if (f.size() < k) {
        fout << "IMPOSSIBLE\n";
    } else {
        fout << s.substr(f[k - 1], s.size() / 2);
    }
    return 0;
}