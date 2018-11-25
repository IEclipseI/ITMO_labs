//
// Created by Роман on 06.05.2018.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    std::ifstream fin("problem5.in");
    std::ofstream fout("problem5.out");
    uint32_t n, m, k, l;
    fin >> n >> m >> k >> l;
    vector<bool> terminalNka(n + 1);
    vector<bool> terminalDka(101);
    uint32_t number_of_set = 1;
    for (int i = 0; i < k; ++i) {
        uint32_t t;
        fin >> t;
        terminalNka[t] = true;
    }
    vector<vector<vector<uint32_t>>> NKA_moves(n + 1, vector<vector<uint32_t >>(26));
    for (int i = 0; i < m; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        NKA_moves[a][c - 'a'].push_back(b);
    }
    vector<vector<vector<int>>> DKA_moves(101, vector<vector<int>>(26));
    map<set<uint32_t>, uint32_t> sets;
    queue<set<uint32_t>> Q;
    set<uint32_t> q;
    q.insert(1);
    sets.insert(pair<set<uint32_t>, uint32_t>(q, 1));
    number_of_set++;
    Q.push(q);
    while (!Q.empty()) {
        q = Q.front();
        Q.pop();
        bool isTerm = false;
        for (size_t i : q) {
            if (terminalNka[i]) {
                isTerm = true;
                break;
            }
        }
        terminalDka[sets.find(q)->second] = isTerm;
        for (size_t i = 0; i < 26; ++i) {
            set<uint32_t> tmp;
            for (uint32_t j : q) {
                for (uint32_t dest : NKA_moves[j][i]) {
                    tmp.insert(dest);
                }
            }
            if (sets.find(tmp) != sets.end()) {
                DKA_moves[sets.find(q)->second][i].push_back(sets.find(tmp)->second);
            } else if (!tmp.empty()){
                Q.push(tmp);
                sets.insert(pair<set<uint32_t >, uint32_t >(tmp, number_of_set));
                DKA_moves[sets.find(q)->second][i].push_back(number_of_set++);
            }
        }
    }
    if (l == 0 && terminalDka[1]) {
        fout << 1 << endl;
        fout.close();
        return 0;
    }
    vector<int> current_set(101);
    vector<int> previous_set(101);
    int mod = 1000000007;
    current_set[1] = 1;
    for (int i = 0; i < l;++i) {
        previous_set = current_set;
        current_set = vector<int>(101);
        for (int j = 1; j <= 100; ++j) {
            for (int sym = 0; sym < 26; ++sym) {
                for (int f = 0; f < DKA_moves[j][sym].size(); ++f) {
                    current_set[DKA_moves[j][sym][f]] = (current_set[DKA_moves[j][sym][f]] + previous_set[j]) % mod;
                }
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= 101; ++i) {
        answer = terminalDka[i]?(answer + current_set[i]) % mod : answer;
    }
    fout << answer << endl;
    fout.close();
    return 0;
}