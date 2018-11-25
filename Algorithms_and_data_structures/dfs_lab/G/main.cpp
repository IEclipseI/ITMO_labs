#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

struct edge {
    ui st = 0;
    ui end;
    ui number = 0;
    bool visited = false;

    explicit edge(ui end) : end(end) {}

    explicit edge(ui st, ui end) : st(st), end(end) {}

    explicit edge(ui st, ui end, ui number) : st(st), end(end), number(number) {}

    edge() : end(0) {};
};

struct vertex {
    ui id;
    ui old_id;
    vec<edge> edges;
    vec<edge> back_edges;
    bool visited;
    ui t_out = 0;
    ui d = UINT32_MAX;
    ui comp_numb = 0;

    explicit vertex(ui id) : id(id), old_id(id), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}

    vertex() : id(0), edges(vec<edge>()), back_edges(vec<edge>()), visited(false) {}
};

vec<edge> get_all_bridges(vec<vertex> graph);

set<ui> get_all_cut_vertexes(vec<vertex> &graph);

void dfs_top_sort(vertex &v, vec<ui> &time_out, vec<vertex> &graph);

bool is_connected(vec<vertex> graph);

bool is_anticyclic(vec<vertex> graph);

ui set_edge_component_color(vec<vertex> &graph);

void count_tout(vec<vertex> &graph);

void dfs_find_full_comp(vec<vertex> &graph);

struct pair_hash {
    size_t operator()(std::pair<ui, ui> const &v) const {
        return v.first * 31 + v.second * 31;
    }
};

struct pair_equals {
    bool operator()(pair<ui, ui> const &v1, pair<ui, ui> const &v2) const {
        return (v1.first == v2.first) && (v1.second == v2.second) || (v1.first == v2.second) && (v1.second == v2.first);
    }
};

struct edge_hash {
    size_t operator()(edge const &e) const {
        return e.st * 31 + e.end;
    }
};


struct edge_equals {
    bool operator()(edge const &e1, edge const &e2) const {
        return (e1.st == e2.st) && (e1.end == e2.end);
    }
};

void fill_set(unordered_set<edge, edge_hash, edge_equals> &edges, vec<vertex> &graph);

struct edge_equals_2 {
    bool operator()(edge const &e1, edge const &e2) const {
        return (e1.st == e2.st) && (e1.end == e2.end);
    }
};


pair<vec<ui>, ui> get_edge_coloring(vec<vertex> graph, size_t m);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ui n, m;
    cin >> n >> m;
    map<string, ui> names;
    map<ui, string> value;
    for (size_t i = 0; i < n; ++i) {
        string s;
        cin >> s;
        value.insert(pair<ui, string>(i, s));
        names.insert(pair<string, ui>(s, i));
    }
    vec<vertex> gr(2 * n);
    for (size_t i = 0; i < 2 * n; ++i) {
        gr[i].id = i;
        gr[i].old_id = i;
    }
    for (size_t i = 0; i < m; ++i) {
        string s, p;
        cin >> s;
        cin >> p;
        cin >> p;
        ui end;
        ui st;
        ui st2;
        ui end2;
        if (s[0] == '-') {
            st = 2 * names.find(s.substr(1, s.size())).operator*().second + 1;
            end2 = 2 * names.find(s.substr(1, s.size())).operator*().second;
        } else {
            st = 2 * names.find(s.substr(1, s.size())).operator*().second;
            end2 = 2 * names.find(s.substr(1, s.size())).operator*().second + 1;
        }
        if (p[0] == '-') {
            end = 2 * names.find(p.substr(1, p.size())).operator*().second + 1;
            st2 = 2 * names.find(p.substr(1, p.size())).operator*().second;
        } else {
            end = 2 * names.find(p.substr(1, p.size())).operator*().second;
            st2 = 2 * names.find(p.substr(1, p.size())).operator*().second + 1;
        }
        gr[st].edges.push_back(edge(st, end, 2 * i));
        gr[end].back_edges.push_back(edge(end, st, 2 * i));
        gr[st2].edges.push_back(edge(st2, end2, 2 * i + 1));
        gr[end2].back_edges.push_back(edge(end2, st2, 2 * i + 1));
    }

    vec<vertex> copy(gr);
    count_tout(copy);
    gr = copy;
    sort(copy.begin(), copy.end(), [](vertex const &a, vertex const &b) { return a.t_out > b.t_out; });
    ui ind = 0;
    for (vertex &v : copy) {
        v.edges.clear();
        v.back_edges.clear();
        v.id = ind++;
        for (edge &e : gr[v.old_id].edges) {
            v.edges.push_back(edge(v.id, gr.size() - gr[e.end].t_out));
        }
        for (edge &e : gr[v.old_id].back_edges) {
            v.back_edges.push_back(edge(v.id, gr.size() - gr[e.end].t_out));
        }
    }
    dfs_find_full_comp(copy);
    for (vertex &v : copy) {
        gr[v.old_id].comp_numb = v.comp_numb;
    }
    for (size_t i = 0; i < n; ++i) {
        if (gr[2 * i].comp_numb == gr[2 * i + 1].comp_numb) {
            cout << -1 << '\n';
            return 0;
        }
    }


    vector<string> s;
    for (size_t i = 0; i < n; ++i) {
        if (gr[2 * i].comp_numb > gr[2 * i + 1].comp_numb) {
            s.push_back(value.find(i).operator*().second);
        }
    }
    if (!s.empty()) {
        cout << s.size() << '\n';
        for (const string &p : s) {
            cout << p << '\n';
        }
    } else {
        cout << -1 << '\n';
    }
    return 0;
}

void fill_set(unordered_set<edge, edge_hash, edge_equals> &edges, vec<vertex> &graph) {
    for (vertex &v : graph) {
        for (edge &e : v.edges) {
            if (v.comp_numb != graph[e.end].comp_numb) {
                edges.insert(edge(v.comp_numb, graph[e.end].comp_numb));
            }
        }
    }
}

void dfs_find_full_comp_impl(vertex &v, vec<vertex> &graph, ui number) {
    v.visited = true;
    v.comp_numb = number;
    for (edge &e : v.back_edges) {
        if (!graph[e.end].visited) dfs_find_full_comp_impl(graph[e.end], graph, number);
    }
}

void dfs_find_full_comp(vec<vertex> &graph) {
    ui comp_numb = 1;
    for (vertex &v : graph) {
        if (!v.visited) dfs_find_full_comp_impl(v, graph, comp_numb++);
    }
    for (vertex &v : graph) {
        v.visited = false;
    }
}

void dfs_tout(vertex &v, vec<vertex> &graph, ui &time) {
    v.visited = true;
    for (edge e : v.edges) {
        if (!graph[e.end].visited) {
            dfs_tout(graph[e.end], graph, time);
        }
    }
    v.t_out = time++;
}

void count_tout(vec<vertex> &graph) {
    ui time_out = 1;
    for (vertex &v : graph) {
        if (!v.visited)dfs_tout(v, graph, time_out);
    }
    for (vertex &v : graph) {
        v.visited = false;
    }
}


size_t get_edge(vec<edge> &edges, ui st, ui end) {
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].end == st && edges[i].st == end) return i;
    }
    return edges.size();
}

void get_edge_coloring_impl(vertex &v, vec<vertex> &graph, ui &max_color, ui cur_color, vec<ui> &answer, ui edge_id) {
    v.visited = true;
    for (edge &e: v.edges) {
        if (!e.visited) {
            e.visited = true;
            graph[e.end].edges[get_edge(graph[e.end].edges, e.st, e.end)].visited = true;
            if (!graph[e.end].visited) {
                if (graph[e.end].d >= v.t_out) {
                    ui new_clr = max_color++;
                    answer[e.number] = new_clr;
                    get_edge_coloring_impl(graph[e.end], graph, max_color, new_clr, answer, edge_id);
                } else {
                    answer[e.number] = cur_color;
                    get_edge_coloring_impl(graph[e.end], graph, max_color, cur_color, answer, edge_id);
                }
            } else if (graph[e.end].d < v.t_out) {
                answer[e.number] = cur_color;
            }
        }
    }
}

pair<vec<ui>, ui> get_edge_coloring(vec<vertex> graph, size_t m) {
    get_all_cut_vertexes(graph);
    vec<ui> answer(m);
    ui max_color = 1;
    for (vertex &v : graph) {
        if (!v.visited) {
            get_edge_coloring_impl(v, graph, max_color, max_color, answer, v.id);
//            max_color++;
        }
    }
    return pair<vec<ui>, ui>(answer, max_color - 1);
}

void get_all_cut_vertexes_impl(vec<vertex> &graph, ui &time, vertex &v, set<ui> &answer, ui edge_id) {
    v.t_out = time;
    v.d = v.t_out;
    time++;
    v.visited = true;
    ui children = 0;
    for (edge e : v.edges) {
        if (e.number != edge_id) {
            if (graph[e.end].visited) {
                v.d = min(v.d, graph[e.end].t_out);
            } else {
                get_all_cut_vertexes_impl(graph, time, graph[e.end], answer, e.number);
                v.d = min(v.d, graph[e.end].d);
                if (v.t_out <= graph[e.end].d && edge_id != 0) answer.insert(e.number);
                children++;
            }
        }
    }
    if (children > 1 && edge_id == 0) {
        answer.insert(v.id);
    }
}

set<ui> get_all_cut_vertexes(vec<vertex> &graph) {
    set<ui> answer;
    ui time = 0;
    if (!graph.empty())
        for (int i = 0; i < graph.size(); ++i) {
            if (!graph[i].visited)
                get_all_cut_vertexes_impl(graph, time, graph[i], answer, UINT32_MAX);
        };
    for (vertex &v : graph) {
        v.visited = false;
    }

    return answer;

}
