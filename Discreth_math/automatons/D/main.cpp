//
// Created by Роман on 25.04.2018.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("problem5.in");
    std::ofstream fout("problem5.out");
    int n, m, k, l;
    fin >> n >> m >> k >> l;
    vector<bool> good(n + 1);
    for (int i = 0; i < k; ++i) {
        int tmp;
        fin >> tmp;
        good[tmp] = true;
    }
    vector<vector<vector<int>>> moves(n + 1, vector<vector<int>>(26));
    int a, b;
    char c;
    for (int i = 0; i < m; ++i) {
        fin >> a >> b >> c;
        moves[a][c - 'a'].push_back(b);
    }
    if (l == 0 && good[1]) {
        fout << 1 << endl;
        fout.close();
        return 0;
    }
    vector<int> current_set(n + 1);
    vector<int> previous_set(n + 1);
    int mod = 1000000007;
    current_set[1] = 1;
    for (int i = 0; i < l;++i) {
        previous_set = current_set;
        current_set = vector<int>(n + 1);
        for (int j = 1; j <= n; ++j) {
            for (int sym = 0; sym < 26; ++sym) {
                for (int f = 0; f < moves[j][sym].size(); ++f) {
                    current_set[moves[j][sym][f]] = (current_set[moves[j][sym][f]] + previous_set[j]) % mod;
                }
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        answer = good[i]?(answer + current_set[i]) % mod : answer;
    }
    fout << answer << endl;
    fout.close();
    return 0;
}
