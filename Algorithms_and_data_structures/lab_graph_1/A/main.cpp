#include <iostream>
#include <vector>

template<typename T>
using vec = std::vector<T>;
    using ui = uint32_t;
    using uill = uint64_t;
using namespace std;

struct vertex;
struct edge;

struct vertex {
    ui id;
    vec<edge> edges;
    vec<edge> back_edges;
    bool visited;
    ui color = 0;

    explicit vertex(ui id) : id(id), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}

    vertex() : id(0), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}
};

struct edge {
    ui end;

    explicit edge(ui end) : end(end) {}

    edge() : end(0) {};
};

void dfs(vertex &v, vec<ui> &time_out, vec<vertex> &graph) {
    if (v.visited) {
        return;
    }
    v.visited = true;
    for (edge e : v.edges) {
        dfs(graph[e.end], time_out, graph);
    }
    time_out.push_back(v.id);
}

bool is_anticyclic_impl(vertex& v, vec<vertex> &graph) {
    if (v.color == 1) {
        return false;
    }
    if (v.color == 2) {
        return true;
    }
    v.color = 1;
    for (edge e : v.edges) {
        if (!is_anticyclic_impl(graph[e.end], graph)) {
            return false;
        }
    }
    v.color = 2;
    return true;
}

bool is_anticyclic(vec<vertex> &graph) {
    for (vertex v:graph) {
        if (v.color == 0) {
            if (!is_anticyclic_impl(v, graph)) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ui n, m;
    cin >> n >> m;
    vec<vertex> graph(n);
    for (ui i = 0; i < n; i++) {
        graph[i].id = i;
    }
    for (ui i = 0; i < m; ++i) {
        ui st, end;
        cin >> st >> end;
        graph[st - 1].edges.push_back(edge(end - 1));
        graph[end - 1].back_edges.push_back(edge(st - 1));
    }
    vec<ui> time_out;
    if (!is_anticyclic(graph)) {
        cout << -1;
    } else {
        for (vertex v : graph) {
            if (v.back_edges.empty()) {
                dfs(v, time_out, graph);
            }
        }
        for(int i = time_out.size() - 1; i >=0; i--) {
            cout << time_out[i] + 1 << " ";
        }
    }
    return 0;
}