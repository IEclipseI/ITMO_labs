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
    ifstream fin;
    vt<vert> G;
    unordered_map<edge *, edge *> redge;
    vt<ll> dist;
    vt<edge *> parent;
    vt<ll> potentials;
    const ll INF = numeric_limits<ll>::max() / 10;


    solve(ll s, ll t, ll n, ll m, ifstream &&fin) : s(s), t(t), n(n), m(m), fin(std::move(fin)) {
        dist = vt<ll>(n, INF);
        dist[s] = 0;
        parent = vt<edge*>(n);
    }

    void read_graph() {
        G.reserve(n);
        for (int i = 0; i < n; ++i) {
            G.emplace_back(i);
        }
        unordered_map<ll, pair<ll, ll>> edges_info;
        for (int i = 0; i < m; ++i) {
            ll from, to, cap, cost;
            fin >> from >> to >> cap >> cost;
            to--;
            from--;
            edge real = edge(from, to, cap, cost);
            edge fake = edge(to, from, 0, -cost);
            edges_info.insert({real.id, {from, G[from].edges.size()}});
            edges_info.insert({fake.id, {to, G[to].edges.size()}});
            G[from].edges.push_back(real);
            G[to].edges.push_back(fake);
        }
        for (int i = 0; i < n; ++i) {
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
            for (int i = 0; i < n; i++) {
                G[i].is_visited = false;
                dist[i] = INF;
            }
            dist[s] = 0;
            while (true) {
                ll i = n;
                for (int j = 0; j < n; ++j) {
                    if (!G[j].is_visited && dist[j] < INF && (i == n  || dist[i] > dist[j]))
                        i = j;
                }
                if (i == n)
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
            for (int i = 0; i < n; ++i) {
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
        vt<vt<ll>> dp(n, vt<ll>(n, INF));
        dp[0][s] = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
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
        return dp[n - 1];
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("mincost.in");
    ofstream fout("mincost.out");

    ll n, m;
    fin >> n >> m;
    vt<vert> G;
    solve sol(0, n - 1, n, m, move(fin));
    sol.read_graph();
    fout << sol.find_min_cost_flow() << '\n';
    return 0;
}