#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("fullham.in");
    ofstream fout("fullham.out");
    ui n;
    fin >> n;
    vec<vec<bool>> g(n, vec<bool>(n));
    for (ui i = 1; i < n; ++i) {
        string s;
        fin >> s;
        for (ui j = 0; j < i; ++j) {
            g[i][j] = static_cast<bool>(s[j] - '0');
            g[j][i] = static_cast<bool>(s[j] - '0');
        }
    }
    deque<ui> deq;
    for (ui i = 0; i < n; ++i) {
        deq.push_back(i);
    }
    for (ui i = 0; i < n * (n - 1); ++i) {
        if (!g[deq[0]][deq[1]]) {
            ui j = 2;
            while (!g[deq[0]][deq[j]] || !g[deq[1]][deq[j + 1]]) {
                j++;
            }
            ui k = 0;
            while (1 + k < j - k) {
                swap(deq[1 + k], deq[j - k]);
                k++;
            }
        }
        deq.push_back(deq[0]);
        deq.pop_front();
    }
    for (unsigned int l : deq) {
        fout << l + 1 << " ";
    }
    fout << "\n";
    fout.close();
    return 0;
}
