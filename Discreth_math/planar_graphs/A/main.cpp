#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;

struct edge {
    int a;
    int b;
    int id;
    double center_x;
    double center_y;

    friend bool operator==(const edge &a, const edge &b);

    edge() = default;

    edge(int a, int b, int id) : a(a), b(b), id(id), center_x(0.f), center_y(0.f) {};
};

bool operator==(const edge &a, const edge &b) {
    return a.a == b.a && a.b == b.b || a.a == b.b && a.b == b.a;
}

struct vertex {
    vec<edge> edges = vec<edge>();
    double x = 0.0;
    double y = 0.0;
    int id = 0;
    int a = 0, b = 0;
    bool visited = false;
    bool color = false;
    int id_ham = 0;
    int a_ham = 0;
    int b_ham = 0;
};

struct edge_hash {
    inline size_t operator()(const edge &a) const {
        return std::hash<int>{}(a.a) ^ std::hash<int>{}(a.b);
    }
};

bool cross(vertex &a, vertex &b) {
    return a.a_ham < b.a_ham
           && b.a_ham < a.b_ham
           && a.b_ham < b.b_ham
           ||
           b.a_ham < a.a_ham
           && a.a_ham < b.b_ham
           && b.b_ham < a.b_ham;
}

bool coloring(vec<vertex> &g, int id, bool color) {
    g[id].color = color;
    g[id].visited = true;
    bool result = true;
    for (auto e : g[id].edges) {
        if (!g[e.b].visited) {
            result = result && coloring(g, e.b, !color);
        } else {
            if (g[e.b].color == g[id].color) {
                return false;
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vec<vertex> V(n);
    for (int i = 0; i < n; ++i) {
        V[i].id = i;
//        V[i].x = 1.0 * i;
//        V[i].y = 0.00000;
    }
    unordered_set<edge, edge_hash> E;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edge tmp(a, b, i);
        E.insert(tmp);
        V[a].edges.push_back(tmp);
        V[b].edges.push_back(tmp);
    }
    vec<vertex> ham;
    int id;
    cin >> id;
    ham.push_back(V[id - 1]);
    ham[0].x = 0.0;
    V[id - 1].x = 0.0;
    V[id - 1].id_ham = 0;
    vec<edge> answer;
    for (int i = 1; i < n; ++i) {
        cin >> id;
        ham.push_back(V[id - 1]);
        ham[i].x = 1.0 * i;
        V[id - 1].x = 1.0 * i;
        V[id - 1].id_ham = i;
        answer.push_back(*E.find(edge(ham[i - 1].id, ham[i].id, 0)));
        answer[answer.size() - 1].center_x = (V[answer[answer.size() - 1].a].x + V[answer[answer.size() - 1].b].x) / 2;
        answer[answer.size() - 1].center_y = 0;
        E.erase(edge(ham[i - 1].id, ham[i].id, 0));

    }
    answer.push_back(*E.find(edge(ham[n - 1].id, ham[0].id, 0)));
    answer[answer.size() - 1].center_x = (V[answer[answer.size() - 1].a].x + V[answer[answer.size() - 1].b].x) / 2;
    answer[answer.size() - 1].center_y = (V[answer[answer.size() - 1].b].x - V[answer[answer.size() - 1].a].x) / 2;
    E.erase(edge(ham[n - 1].id, ham[0].id, 0));

    vec<vertex> ed;
    for (edge e: E) {
        ed.push_back(vertex());
        ed[ed.size() - 1].id = e.id;
//        ed[ed.size() - 1].a = e.a;
//        ed[ed.size() - 1].b = e.b;
        ed[ed.size() - 1].a_ham = min(V[e.a].id_ham, V[e.b].id_ham);
        ed[ed.size() - 1].b_ham = max(V[e.a].id_ham, V[e.b].id_ham);
    }
    for (int i = 0; i < ed.size(); ++i) {
        for (int j = i + 1; j < ed.size(); ++j) {
            if (cross(ed[i], ed[j])) {
                ed[i].edges.push_back(edge(i, j, 0));
                ed[j].edges.push_back(edge(j, i, 0));
            }
        }
    }

    if (E.size() == 0 || coloring(ed, 0, true)) {
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            cout << setprecision(numeric_limits<double>::digits10 + 1) << V[i].x << " " << V[i].y << " ";
        }
        cout << "\n";
        for (auto v : ed) {
            answer.push_back(edge(v.a_ham, v.b_ham, v.id));
            answer[answer.size() - 1].center_x =
                    (ham[answer[answer.size() - 1].a].x + ham[answer[answer.size() - 1].b].x) / 2;
            if (v.color) {
                answer[answer.size() - 1].center_y =
                        (ham[answer[answer.size() - 1].b].x - ham[answer[answer.size() - 1].a].x) / 2;
            } else {
                answer[answer.size() - 1].center_y = -(ham[answer[answer.size() - 1].b].x -
                                                       ham[answer[answer.size() - 1].a].x) / 2;
            }
        }
        sort(answer.begin(), answer.end(), [](const edge& a, const edge& b){ return a.id < b.id;});
        for (int i = 0; i < answer.size(); ++i) {
            cout << answer[i].center_x << " " << answer[i].center_y << "\n";
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}