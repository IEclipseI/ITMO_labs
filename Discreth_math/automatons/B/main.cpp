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
    std::ifstream fin("problem2.in");
    std::ofstream fout("problem2.out");
    string s;
    fin>>s;
    int n, m , k;
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
    vector<vector<vector<int>>> moves(n + 1, vector<vector<int>>(26));
    int a, b;
    char c;
    for (int i = 0; i < m; ++i) {
        fin >> a >> b >> c;
        moves[a][c - 'a'].push_back(b);
    }
    if (s[0] <= '9' && s[0] >= '0') {
        if (good[1]) {
            fout << "Accepts" << endl;
        } else {
            fout << "Rejects" << endl;
        }
        return 0;
    }
    unordered_set<int> current_set;
    unordered_set<int> previous_set;
    current_set.insert(1);
    for (int i = 0; i < s.length(); ++i) {
        swap(current_set, previous_set);
        current_set.clear();
        for(int it : previous_set) {
            for (int vershina: moves[it][s[i] - 'a']) {
                current_set.insert(vershina);
            }
        }
    }
    for (int j : current_set) {
        if (good[j]) {
            fout << "Accepts" << endl;
            fout.close();
            return 0;
        }
    }
    fout << "Rejects" << endl;
    fout.close();
    return 0;
}
