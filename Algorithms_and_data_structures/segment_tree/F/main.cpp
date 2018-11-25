//
// Created by Роман on 11.04.2018.
//
#include <iostream>
#include <fstream>
#include <cmath>

uint32_t sparse[100000][1000];

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("sparse.in");
    ofstream fout("sparse.out");

    uint64_t n, m;
    uint64_t a1, u1, v1;
    fin >> n >> m >> a1 >> u1 >> v1;
    uint32_t max_length = floor(log(n) / log(2));
    for (int i = 0; i < n; ++i) {
        sparse[i][0] = a1;
        a1 = (23 * a1 + 21563) % 16714589;
    }
    uint32_t two_pow[1000];
    uint32_t log_n[100000];
    for (int i = 1; i <= 100000; ++i) {
        uint32_t j = i - 1;
        log_n[i - 1] = 0;
        while (j > 1) {
            log_n[i - 1]++;
            j >>= 1;
        }
    }
    two_pow[0] = 1;
    for (int j = 0; j < max_length; ++j) {
        two_pow[j + 1] = 2 * two_pow[j];
    }
    for (int i = 1; i <= max_length; ++i) {
        for (int j = 0; j <= n - two_pow[i]; ++j) {
            sparse[j][i] = min(sparse[j][i - 1], sparse[j + two_pow[i - 1]][i - 1]);
        }
    }
    uint32_t f = sparse[u1 - 1][log_n[v1 - u1 + 1]];
    uint32_t s = sparse[v1 - two_pow[log_n[v1 - u1 + 1]]][log_n[v1 - u1 + 1]];
    uint64_t ans = min(sparse[u1 - 1][log_n[v1 - u1 + 1]],
                       sparse[v1 - two_pow[log_n[v1 - u1 + 1]]][log_n[v1 - u1 + 1]]);
    for (int i = 1; i < m; ++i) {
        u1 = ((17ll * u1 + 751 + ans + 2 * i) % n) + 1;
        v1 = ((13ll * v1 + 593 + ans + 5 * i) % n) + 1;
        if (u1 > v1) {
            uint32_t tmp = u1;
            u1 = v1;
            v1 = tmp;
            ans = min(sparse[u1 - 1][log_n[v1 - u1 + 1]], sparse[v1 - two_pow[log_n[v1 - u1 + 1]]][log_n[v1 - u1 + 1]]);
            tmp = u1;
            u1 = v1;
            v1 = tmp;
        } else {
            ans = min(sparse[u1 - 1][log_n[v1 - u1 + 1]], sparse[v1 - two_pow[log_n[v1 - u1 + 1]]][log_n[v1 - u1 + 1]]);
        }
    }

    fout << u1<< " " << v1 << " " << ans << endl;
    fout.close();
    return 0;
}
