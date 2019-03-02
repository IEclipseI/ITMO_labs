#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>


using namespace std;
template<class T>
using vec = vector<T>;
using ll = int64_t;

struct DSU {
    vec<int> parent;
    vec<int> rank;
    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }
    DSU(size_t n):parent(vec<int>(n)), rank(vec<int>(n)) {
        for (int i = 0; i < n; ++i) {
            make_set(i);
        }
    };
};

struct task {
    ll d = 0, w = 0;
};

struct edge {
    ll a = 0, b = 0, w = 0, id = 0;
};

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("destroy.in");
    ofstream fout("destroy.out");
    fin.tie(nullptr);

    size_t n, m;
    ll s;
    fin >> n >> m >> s;
    DSU dsu(n);
    vec<pair<edge, bool>> edges;
    for (int i = 0; i < m; ++i) {
        edge e;
        fin >> e.a >> e.b >> e.w;
        e.a--;
        e.b--;
        e.id = i + 1;
        edges.push_back(make_pair(e, true));
    }
    sort(edges.begin(), edges.end(), [](const pair<edge, bool>& a, const pair<edge, bool>& b) { return a.first.w > b.first.w;});
    for (int i = 0; i < m; ++i) {
        if (dsu.find_set(edges[i].first.a) != dsu.find_set(edges[i].first.b)) {
            edges[i].second = false;
            dsu.union_sets(edges[i].first.a, edges[i].first.b);
        }
    }
    vec<edge> answer;
    for (int i = m - 1; i >= 0; --i) {
        if (edges[i].second) {
            if (s - edges[i].first.w >= 0) {
                answer.push_back(edges[i].first);
                s -= edges[i].first.w;
            } else {
                break;
            }
        }
    }
    sort(answer.begin(), answer.end(), [](const edge& a, const edge& b) { return a.id < b.id;});
    fout << answer.size() << "\n";
    for (int i = 0; i < answer.size(); ++i) {
        fout << answer[i].id << " ";
    }
    return 0;
}