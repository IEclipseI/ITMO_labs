#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <fstream>
#include <list>
#include <cmath>
#include <iomanip>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

struct vertex {
    vertex(ui id, double weigth, ui end_id) : id(id), weight(weigth), end_id(end_id) {}

    ui id = 0;
    double weight = 0;
    ui end_id = 0;
};

struct edge {
    edge(ui st, ui end, uill w) : st(st), end(end), w(w) {}

    ui st = 0;
    ui end = 0;
    uill w = 0;
};

struct dsu {
    explicit dsu(ui n) : parent(vec<ui>(n)), rank(vec<ui>(n)) {
        for (size_t i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    vec<ui> parent;
    vec<ui> rank;

    ui find_set(ui v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(ui a, ui b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            if (rank[a] < rank[b])
                swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ui n, m;
    cin >> n >> m;
    vec<edge> edges;
    edges.reserve(m);
    for (size_t i = 0; i < m; ++i) {
        uill st, end, w;
        cin >> st >> end >> w;
        edges.emplace_back(st - 1, end - 1, w);
    }
    sort(edges.begin(), edges.end(), [](edge const &a, edge const &b) {
        return a.w < b.w;
    });
    uill answer = 0;
    dsu dsu_(n);
    for (edge &e: edges) {
        if (dsu_.find_set(e.st) != dsu_.find_set(e.end)) {
            dsu_.union_sets(e.st, e.end);
            answer+= e.w;
        }
    }
    cout << answer << '\n';
    return 0;
}
