#include <iostream>
#include <vector>
#include <algorithm>

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
    ui t_in = 0;
    ui d = UINT32_MAX;

    explicit vertex(ui id) : id(id), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}

    vertex() : id(0), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}
};

struct edge {
    ui end;
    ui number = 0;

    explicit edge(ui end) : end(end) {}

    explicit edge(ui end, ui number) : end(end), number(number) {}

    edge() : end(0) {};
};

vec<std::pair<unsigned int, unsigned int>> get_all_bridges_impl();

void dfs_top_sort(vertex &v, vec<ui> &time_out, vec<vertex> &graph) {
    if (v.visited) {
        return;
    }
    v.visited = true;
    for (edge e : v.edges) {
        dfs_top_sort(graph[e.end], time_out, graph);
    }
    time_out.push_back(v.id);
}

bool is_anticyclic_impl(vertex &v, vec<vertex> &graph) {
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

void get_all_bridges_impl(vec<vertex> &graph, ui &time, vertex &v, vec<ui> &answer, ui parent_id) {
    v.t_in = time;
    v.d = v.t_in;
    time++;
    v.visited = true;
    for (edge e : v.edges) {
        if (e.end != parent_id) {
            if (graph[e.end].visited) {
                v.d = min(v.d, graph[e.end].t_in);
            } else {
                get_all_bridges_impl(graph, time, graph[e.end], answer, v.id);
                v.d = min(v.d, graph[e.end].d);
                if (v.t_in < graph[e.end].d) answer.push_back(e.number);
            }
        }
    }
}

vec<ui> get_all_bridges(vec<vertex> &graph) {
    vec<ui> answer;
    ui time = 0;
    for (ui i = 0; i < graph.size(); ++i) {
        if (!graph[i].visited) {
            get_all_bridges_impl(graph, time, graph[i], answer, graph[i].id);
        }
    }
    return answer;
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
        graph[st - 1].edges.push_back(edge(end - 1, i + 1));
        graph[end - 1].edges.push_back(edge(st - 1, i + 1));
    }
    vec<ui> answer = get_all_bridges(graph);
    sort(answer.begin(), answer.end(), [](ui a, ui b) { return a < b;});
    cout << answer.size() << '\n';
    for (ui p : answer) {
        cout << p << " ";
    }

    return 0;
}