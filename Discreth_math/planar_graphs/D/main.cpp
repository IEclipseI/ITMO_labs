#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;

bool next_combination (vector<int> & a, int n) {
    int k = (int)a.size();
    for (int i=k-1; i>=0; --i)
        if (a[i] < n-k+i+1) {
            ++a[i];
            for (int j=i+1; j<k; ++j)
                a[j] = a[j-1]+1;
            return true;
        }
    return false;
}

bool is_planar(vec<vec<bool>> g, ui size) {
    bool f = false;
    bool s = false;

    vec<vec<bool>> g1(g);
    if (size == 6) {
        for (int i = 0; i < size; ++i) {
            for (int l = 0; l < size; ++l) {
                bool flag = true;
                vec<vec<bool>> g11(g);
                if (l != i && g[l][i]) {
                    for (int t = 0; t < size; ++t) {
                        g11[l][t] = g11[l][t] || g[i][t];
                    }
                }
                for (int j = 0; j < size; ++j) {
                    if (j == i) continue;
                    for (int k = 0; k < j; ++k) {
                        if (k == i) continue;
                        if (!g11[j][k]) {
                            flag = false;
                            break;
                        }
                    }
                }
                f = f || flag;
            }
        }
    }
    if (size == 5) {
        bool flag = true;
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < j; ++k) {
                if (!g1[j][k]) {
                    flag = false;
                    break;
                }
            }
        }
        f = f || flag;
    }

    if (size == 6) {
        vec<int> C = {1,2,3};
        for (int i = 0; i < 10; ++i) {
            bool flag = true;
            set<int> left(C.begin(), C.end());
            set<int> right;
            for (int j = 1; j <= 6; ++j) {
                if (left.find(j) == left.end()) {
                    right.insert(j);
                }
            }
            for (auto k : left) {
                for(auto m : right) {
                    if (!g1[k - 1][m - 1])
                        flag = false;
                }
            }
            next_combination(C, 6);
            s = s || flag;
        }
    }

    return !f && !s;
}


int main() {
//    ios_base::sync_with_stdio(false);
    ifstream fin("planaritycheck.in");
//    fin.tie(nullptr);

    ofstream fout("planaritycheck.out");

    int t;
    fin >> t;
    string s;
    getline(fin, s);
    for (int i = 0; i < t; ++i) {
        getline(fin, s);
        if (s.length() <= 6) {
            fout << "YES\n";
            continue;
        } else {
            vec<vec<bool>> g;
            if (s.length() == 10) {
                g = vec<vec<bool>>(5, vec<bool>(5, false));
                ui ind = 0;
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < j + 1; ++k) {
                        g[j + 1][k] = static_cast<bool>(s[ind] - '0');
                        g[k][j + 1] = static_cast<bool>(s[ind] - '0');
                        ind++;
                    }
                }
                if (is_planar(g, 5)) {
                    fout << "YES\n";
                } else {
                    fout << "NO\n";
                }
            } else {
                g = vec<vec<bool>>(6, vec<bool>(6, false));
                ui ind = 0;
                for (int j = 0; j < 5; ++j) {
                    for (int k = 0; k < j + 1; ++k) {
                        g[j + 1][k] = static_cast<bool>(s[ind] - '0');
                        g[k][j + 1] = static_cast<bool>(s[ind] - '0');
                        ind++;
                    }
                }
                if (is_planar(g, 6)) {
                    fout << "YES\n";
                } else {
                    fout << "NO\n";
                }
            }

        }
    }

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}