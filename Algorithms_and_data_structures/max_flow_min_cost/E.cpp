#include <utility>

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

template<typename T>
using vt = vector<T>;

using ll = int64_t;

template<typename FROM, typename TO>
using umap = unordered_map<FROM, TO>;

struct edge {
    ll id;
    ll from;
    ll to;
    ll cap;
    ll cost;
    ll flow;

    edge(ll from, ll to, ll cap, ll cost) : from(from), to(to), cap(cap), cost(cost), flow(0ll) {
        static ll g_id = 0;
        id = g_id++;
    }

    bool operator==(const edge &other) const {
        return id == other.id;
    }

    bool is_full() {
        return flow == cap;
    }
};

struct hash_edge {
    int operator()(const edge &e) const {
        return e.id;
    }
};

struct vert {
    ll id;
    vt<edge> edges;
    bool is_visited;

    vert(ll id) : id(id), edges{}, is_visited(false) {}
};

struct solve {
    ll s;
    ll t;
    ll n;
    ll m;
    ll size;
    ifstream fin;
    vt<vert> G;
    unordered_map<edge *, edge *> redge;
    unordered_map<ll, pair<ll, ll>> edges_info;
    vt<ll> dist;
    vt<edge *> parent;
    vt<ll> potentials;
    const ll INF = numeric_limits<ll>::max() / 10;


    solve(ll n, ll m) : n(n), m(m) {
        s = 2 * n;
        t = 2 * n + 1;
        size = 2 * n + 2;
        dist = vt<ll>(size, INF);
        dist[s] = 0;
        parent = vt<edge *>(size);
    }


    void add_edge(ll from, ll to, ll cap, ll cost) {
        edge real = edge(from, to, cap, cost);
        edge fake = edge(to, from, 0, -cost);
        edges_info.insert({real.id, {from, G[from].edges.size()}});
        edges_info.insert({fake.id, {to, G[to].edges.size()}});
        G[from].edges.push_back(real);
        G[to].edges.push_back(fake);
    }

    void read_graph() {
        G.reserve(size);
        for (int i = 0; i < 2 * n; ++i) {
            G.emplace_back(i);
        }
        G.emplace_back(2 * n);
        G.emplace_back(2 * n + 1);
        for (int i = 0; i < n; ++i) {
            ll cost;
            cin >> cost;
            add_edge(i * 2, i * 2 + 1, n, 0);
            add_edge(i * 2 + 1, i * 2, n, cost);
        }
        for (int i = 0; i < m; ++i) {
            ll from;
            ll to;
            ll cost;
            cin >> from >> to >> cost;
            from--;
            to--;
            add_edge(from * 2 + 1, to * 2, n, cost);
        }
        for (int i = 0; i < n; ++i) {
            add_edge(2 * n, 2 * i + 1, 1, 0);
            add_edge(2 * i, 2 * n + 1, 1, 0);
        }

        for (int i = 0; i < size; ++i) {
            for (auto &p : G[i].edges) {
                edge *real = &p;
                auto tmp = edges_info.find(real->id ^ 1ll);
                edge *fake = &G[tmp->second.first].edges[tmp->second.second];
                redge.insert({real, fake});
            }
        }
    }

    ll find_min_cost_flow() {
        ll answer = 0;
        potentials = init_potentials();
        while (true) {
            for (int i = 0; i < size; i++) {
                G[i].is_visited = false;
                dist[i] = INF;
            }
            dist[s] = 0;
            while (true) {
                ll i = size;
                for (int j = 0; j < size; ++j) {
                    if (!G[j].is_visited && dist[j] < INF && (i == size || dist[i] > dist[j]))
                        i = j;
                }
                if (i == size)
                    break;
                G[i].is_visited = true;
                for (auto &e : G[i].edges) {
                    if (!e.is_full()) {
                        ll to = e.to;
                        if (!G[to].is_visited && dist[to] > dist[i] + e.cost - potentials[to] + potentials[i]) {
                            dist[to] = dist[i] + e.cost - potentials[to] + potentials[i];
                            parent[to] = &e;
                        }
                    }
                }
            }
            if (!G[t].is_visited) {
                break;
            }
            for (int i = 0; i < size; ++i) {
                potentials[i] = ((potentials[i] >= INF) ? potentials[i] : potentials[i] + dist[i]);
            }
            ll minimum = INF;
            ll added = 0;
            for (int i = t; i != s;) {
                int tmp = parent[i]->from;
                minimum = min(minimum, parent[i]->cap - parent[i]->flow);
                i = tmp;
            }
            for (int i = t; i != s;) {
                int tmp = parent[i]->from;
                parent[i]->flow += minimum;
                redge.find(parent[i])->second->flow -= minimum;
                added += parent[i]->cost * minimum;
                i = tmp;
            }
            answer += added;
        }
        return answer;
    }


    vt<ll> init_potentials() {
        vt<vt<ll>> dp(size, vt<ll>(size, INF));
        dp[0][s] = 0;
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                dp[i][j] = dp[i - 1][j];
            }
            for (auto &p:redge) {
                if (p.first->is_full())
                    continue;
                dp[i][p.first->to] = min(dp[i][p.first->to],
                                         dp[i - 1][p.first->from] == INF ? INF : (dp[i - 1][p.first->from] +
                                                                                  p.first->cost));
            }
        }
        return dp[size - 1];
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    ifstream fin("assignment.in");
//    ofstream fout("assignment.out");

    ll n, m;
    cin >> n >> m;
    vt<vert> G;
    solve sol(n, m);
    sol.read_graph();
    cout << sol.find_min_cost_flow() << '\n';
    return 0;
}