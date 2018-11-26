#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>

const double eps = 0.000000000000001;
const double eps_p = 0.000000000001;
const double eps_s = 0.000000005;
int v_id = 0;
int e_id = 0;

using namespace std;

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;

struct edge {
    int a = 0;
    int b = 0;
    int id = 0;
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    double angle = 0.0;
    bool visited = false;
    int ind = 0;

    friend bool operator==(const edge &a, const edge &b);

    edge() = default;

    edge(int a, int b, int id, double x1, double y1, double x2, double y2, double angle) : a(a), b(b), id(id), x1(x1),
                                                                                           y1(y1), x2(x2),
                                                                                           y2(y2), angle(angle) {};
};

struct vertex {
    vec<edge> edges = vec<edge>();
    double x = 0.0;
    double y = 0.0;
    int id = 0;
};

struct line {
    double x1 = 0.0, y1 = 0.0,
            x2 = 0.0, y2 = 0.0;
    double x = 0.0, y = 0.0;
    double A = 0.0;
    double B = 0.0;
    double C = 0.0;
    vec<vertex> V;
};

bool parallel(line &l1, line &l2) {
    double l = l1.x / l1.y - l2.x / l2.y;
    double r = (l1.y / l1.x - l2.y / l2.x);
    return abs(l) < eps_p || abs(r) < eps_p;
}

double dist(vertex &a, vertex &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void add_point(line &l1, line &l2) {
    if (!parallel(l1, l2)) {
        double x = (l1.C * l2.B - l1.B * l2.C) / (l1.A * l2.B - l1.B * l2.A);
        double y = (l1.A * l2.C - l1.C * l2.A) / (l1.A * l2.B - l1.B * l2.A);
        bool f1 = true;
        bool f2 = true;
        vertex v;
        v.x = x;
        v.y = y;
        int cur_id = INT32_MAX;
        for (auto &p : l1.V) {
            if (dist(p, v) < eps) {
                f1 = false;
                cur_id = p.id;
            }
        }
        for (auto &p : l2.V) {
            if (dist(p, v) < eps) {
                f2 = false;
                cur_id = p.id;
            }
        }
        if (f1 && f2) {
            v.id = v_id++;
        } else {
            v.id = cur_id;
        }
        if (f1)
            l1.V.push_back(v);
        if (f2)
            l2.V.push_back(v);
    }

}

void setABC(line &l) {
    l.A = l.y1 - l.y2;
    l.B = l.x2 - l.x1;
    l.C = -(l.x1 * l.y2 - l.x2 * l.y1);
}

double angle(double x2, double y2) {
    double t = x2 / sqrt(x2 * x2 + y2 * y2);
    if (t < -1) t = -1;
    else if (t > 1) t = 1;
    double ang = acos(t);
    if (y2 < 0) {
        ang = M_PI * 2.0 - ang;
    }
    return ang;
}

bool operator==(const edge &a, const edge &b) {
    return a.a == b.a && a.b == b.b || a.a == b.b && a.b == b.a;
}

struct vert_less {
    bool operator()(const vertex &a, const vertex &b) const {
        return a.id < b.id;
    }
};

int get_edge_ind(edge &from, vertex &cur) {
    int res = 0;
    while (cur.edges[res].id != from.id) {
        res++;
    }
    return res;
}

void dfs(vec<vertex> &G, edge &from, vec<vertex> &res, vertex &cur, vec<bool> &visited, vec<edge> &E) {
    visited[from.ind] = true;
    if (cur.id == res[0].id) {
        return;
    }
    int edge_ind = get_edge_ind(from, cur);
    edge_ind = (edge_ind + 1) % cur.edges.size();
    res.push_back(cur);
    dfs(G, cur.edges[edge_ind].a == E[2 * cur.edges[edge_ind].id].a ? E[2 * cur.edges[edge_ind].id] : E[
            2 * cur.edges[edge_ind].id + 1], res, G[cur.edges[edge_ind].b], visited, E);
}

void find_faces(vec<vec<vertex>> &faces, vec<vertex> &G, vec<edge> &E) {
    vec<bool> visited(E.size(), false);
    for (int i = 0; i < E.size(); ++i) {
        if (!visited[E[i].ind]) {
            vec<vertex> res1;
            res1.push_back(G[E[i].a]);
            dfs(G, E[i], res1, G[E[i].b], visited, E);
            faces.push_back(res1);
        }
    }
}

double get_square(vec<vertex> &face) {
    double answer = 0;
    answer += (face[0].x - face[face.size() - 1].x) * (face[0].y + face[face.size() - 1].y);
    for (int i = 1; i < face.size(); ++i) {
        answer += (face[i].x - face[i - 1].x) * (face[i].y + face[i - 1].y);
    }
    answer = abs(answer);
    return answer / 2.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vec<line> lines;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        line l;
        cin >> l.x1 >> l.y1 >> l.x2 >> l.y2;
        l.x = l.x2 - l.x1;
        l.y = l.y2 - l.y1;
        setABC(l);
        for (int j = 0; j < lines.size(); ++j) {
            add_point(l, lines[j]);
        }
        lines.push_back(l);
    }
    set<vertex, vert_less> V;
    for (auto &l : lines) {
        if (l.x != 0) {
            sort(l.V.begin(), l.V.end(), [](const vertex &a, const vertex &b) { return a.x < b.x; });
        } else {
            sort(l.V.begin(), l.V.end(), [](const vertex &a, const vertex &b) { return a.y < b.y; });
        }
        if (!l.V.empty()) {
            if (V.find(l.V[0]) == V.end()) {
                V.insert(l.V[0]);
            }
            for (int i = 1; i < l.V.size(); ++i) {
                vertex &v1 = const_cast<vertex &>(*V.find(l.V[i - 1]));
                edge edge1(v1.id, l.V[i].id, e_id, v1.x, v1.y, l.V[i].x, l.V[i].y,
                           angle(l.V[i].x - v1.x, l.V[i].y - v1.y));
                edge edge2(l.V[i].id, v1.id, e_id++, l.V[i].x, l.V[i].y, v1.x, v1.y,
                           angle(v1.x - l.V[i].x, v1.y - l.V[i].y));
                if (V.find(l.V[i]) == V.end()) {
                    V.insert(l.V[i]);
                }
                v1.edges.push_back(edge1);
                vertex &v2 = const_cast<vertex &>(*V.find(l.V[i]));
                v2.edges.push_back(edge2);
            }
        }
    }
    vec<vertex> G(V.begin(), V.end());
    vec<edge> E;
    for (auto &v : G) {
        sort(v.edges.begin(), v.edges.end(), [](const edge &a, const edge &b) { return a.angle < b.angle; });
        for (auto &e : v.edges) {
            E.push_back(e);
        }
    }

    sort(E.begin(), E.end(), [](edge const &a, edge const &b) { return a.id < b.id; });
    for (int i = 0; i < E.size(); ++i) {
        E[i].ind = i;
    }
    vec<vec<vertex>> faces;
    find_faces(faces, G, E);
    vec<double> final;
    for (int i = 0; i < faces.size(); ++i) {
        double t = get_square(faces[i]);
        if (t >= eps_s) {
            final.push_back(t);
        }
    }
    if (final.empty()) {
        cout << 0;
    } else {
        cout << final.size() - 1 << "\n";
        sort(final.begin(), final.end(), [](double a, double b) { return a < b; });
        for (int i = 0; i < final.size() - 1; ++i) {
            cout << setprecision(std::numeric_limits<long double>::digits10 + 1) << final[i] << "\n";
        }
    }
    return 0;
}