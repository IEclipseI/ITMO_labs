//
// Created by Роман on 14.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool checking_equality(queue<pair<uint32_t, uint32_t>> &queue1,
                       vector<vector<uint32_t>> &moves1,
                       vector<vector<uint32_t>> &moves2,
                       vector<bool> &terminal1,
                       vector<bool> &terminal2,
                       vector<vector<bool>> &visited) {
    while (!queue1.empty()) {
        pair<uint32_t, uint32_t> p = queue1.front();
        queue1.pop();
        if (terminal1[p.first] != terminal2[p.second]) {
            return false;
        }
        visited[p.first][p.second] = true;
        for (int i = 0; i < 26; ++i) {
            if (!visited[moves1[p.first][i]][moves2[p.second][i]]) {
                queue1.push(pair<uint32_t, uint32_t>(moves1[p.first][i], moves2[p.second][i]));
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("equivalence.in");
    ofstream fout("equivalence.out");

    uint32_t n1, m1, k1;
    fin >> n1 >> m1 >> k1;
    vector<vector<uint32_t>> moves1(n1 + 1, vector<uint32_t>(26));
    vector<bool> terminal1(n1 + 1);
    for (int i = 0; i < k1; ++i) {
        uint32_t t;
        fin >> t;
        terminal1[t] = true;
    }
    for (int i = 0; i < m1; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        moves1[a][c - 'a'] = b;
    }
    uint32_t n2, m2, k2;
    fin >> n2 >> m2 >> k2;
    vector<vector<uint32_t>> moves2(n2 + 1, vector<uint32_t>(26));
    vector<bool> terminal2(n2 + 1);
    for (int i = 0; i < k2; ++i) {
        uint32_t t;
        fin >> t;
        terminal2[t] = true;
    }
    for (int i = 0; i < m2; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        moves2[a][c - 'a'] = b;
    }
    vector<vector<bool>> visited(n1 + 1, vector<bool>(n2 + 1));
    queue<pair<uint32_t, uint32_t>> queue1;
    queue1.push(pair<uint32_t, uint32_t>(1, 1));
    fout << (checking_equality(queue1, moves1, moves2, terminal1, terminal2, visited)?"YES":"NO") << endl;
    fout.close();
    return 0;
}