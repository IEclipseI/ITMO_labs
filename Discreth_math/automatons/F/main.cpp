//
// Created by Роман on 05.05.2018.
//
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace std {
    template<>
    struct hash<pair<uint32_t, char>> {
        inline size_t operator()(const pair<uint32_t, char> &v) const {
            return hash<uint32_t>()(v.first) ^ hash<char>()(v.second);
        }
    };
}
bool isDevil(uint32_t u,
             vector<vector<uint32_t>> &uTransitions,
             vector<bool> &uVertexes) {
    if (uVertexes[u]) {
        return false;
    }
    for (int i = 0; i < uTransitions[u].size(); ++i) {
        if (!uTransitions[u][i]) {
            return false;
        }
    }
    return true;
}
bool dfs(uint32_t u, uint32_t v,
         vector<vector<uint32_t>> &uTransitions,
         vector<vector<uint32_t>> &vTransitions,
         vector<bool> &uVertexes,
         vector<bool> &vVertexes,
         vector<bool> &visited) {
    visited[u] = true;
    if (uVertexes[u] != vVertexes[v]) {
        return false;
    }
    bool result = true;
    vector<uint32_t> tmp = uTransitions[u];
    for (size_t i = 0; i < tmp.size(); i++) {
        if (tmp[i] == 0){
            continue;
        }
        uint32_t t1 = uTransitions[u][i];
        uint32_t t2 = vTransitions[v][i];
        if (t1 == 0 && t2 != 0 || t1 != 0 && t2 == 0) {
            return false;
        }
        if (isDevil(t1, uTransitions, uVertexes) != isDevil(t2, vTransitions, vVertexes)) {
            return false;
        }
        if (!visited[t1]) {
            result = result && dfs(t1, t2, uTransitions, vTransitions, uVertexes, vVertexes, visited);
        }
    }
    return result;
}


int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("isomorphism.in");
    ofstream fout("isomorphism.out");
    uint32_t n1, m1, k1;
    fin >> n1 >> m1 >> k1;
    vector<bool> aVertexes(n1 + 1);
    vector<vector<uint32_t>> aTransitions(m1 + 1, vector<uint32_t>(26));
    for (int i = 0; i < k1; ++i) {
        int tmp;
        fin >> tmp;
        aVertexes[tmp] = true;
    }
    for (int i = 0; i < m1; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        aTransitions[a]['z' - c] = b;
    }
    uint32_t n2, m2, k2;
    fin >> n2 >> m2 >> k2;
    vector<bool> bVertexes(n2 + 1);
    vector<vector<uint32_t>> bTransitions(m2 + 1, vector<uint32_t>(26));
    for (int i = 0; i < k2; ++i) {
        int tmp;
        fin >> tmp;
        bVertexes[tmp] = true;
    }
    for (int i = 0; i < m2; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        bTransitions[a]['z' - c] = b;
    }
    if (n1 != n2 || m1 != m2 || k1 != k2) {
        fout << "NO" << endl;
        return 0;
    }
    vector<bool> visited(n1 + 1, false);
    fout << (dfs(1, 1, aTransitions, bTransitions, aVertexes, bVertexes, visited)?"YES":"NO") << endl;
    return 0;
}