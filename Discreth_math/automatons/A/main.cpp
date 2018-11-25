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
    std::ifstream fin("problem1.in");
    std::ofstream fout("problem1.out");
    string s;
    fin >> s;
    int n, m, k;
    if (s[0] <= '9' && s[0] >= '0') {
        n = std::stoi(s);
        fin >> m;
        fin >> k;
    } else {
        fin >> n >> m >> k;
    }
    vector<bool> good(n + 1);
    for (int i = 0; i < k; ++i) {
        int tmp;
        fin >> tmp;
        good[tmp] = true;
    }

    vector<vector<int>> moves(n + 1, vector<int>(26));
    int a, b;
    char c;
    for (int j = 0; j < m; ++j) {
        fin >> a >> b >> c;
        moves[a][c - 'a'] = b;
    }
    if (s[0] <= '9' && s[0] >= '0') {
        if (good[1]) {
            fout << "Accepts" << endl;
        } else {
            fout << "Rejects" << endl;
        }
        return 0;
    }
    int previous = 1;
    for (int i = 0; i < s.length(); ++i) {
        previous = moves[previous][s[i] - 'a'];
    }
    if(good[previous]) {
        fout << "Accepts" << endl;
    } else {
        fout << "Rejects" << endl;
    }
    fout.close();
    return 0;
}
