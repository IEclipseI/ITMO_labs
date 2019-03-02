#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <fstream>
#include <list>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

void dfs_check(ui v, vec<vec<ui>> &gr, vec<bool> &visited, int dist) {
    visited[v] = true;
    for (size_t i = 0; i < gr[v].size(); i++) {
        if (!visited[i] && gr[v][i] <= dist) {
            dfs_check(i, gr, visited, dist);
        }
    }
}

void dfs_check_back(ui v, vec<vec<ui>> &gr, vec<bool> &visited, int dist) {
    visited[v] = true;
    for (size_t i = 0; i < gr[v].size(); i++) {
        if (!visited[i] && gr[i][v] <= dist) {
            dfs_check_back(i, gr, visited, dist);
        }
    }
}

bool is_connected_by_dist(vec<vec<ui>> &gr, int dist) {
    vec<bool> a(gr.size(), false);
    dfs_check(0, gr, a, dist);
    for (bool v : a) {
        if (!v) return false;
    }
    vec<bool> b(gr.size(), false);
    dfs_check_back(0, gr, b, dist);
    for (bool v : b) {
        if (!v) return false;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    ifstream fin("avia.in");
    ofstream fout("avia.out");
    cin.tie(nullptr);
    ui n;
    cin >> n;
    vec<vec<ui>> gr(n, vec<ui>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            cin >> gr[i][j];
        }
    }
    vec<bool> a(n, false);
    int lb = -1;
    int ub = 1000000000;
    while (lb < ub - 1) {
        if (is_connected_by_dist(gr, (ub + lb) / 2))
            ub = (ub + lb) / 2;
        else
            lb = (ub + lb) / 2;
    }

    cout << ub << '\n';
    fout.close();
    return 0;
}
