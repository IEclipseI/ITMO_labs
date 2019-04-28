#include <utility>

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <deque>
#include <algorithm>

using namespace std;

template<typename T>
using vt = vector<T>;

using ll = int64_t;
static const ll INF = numeric_limits<ll>::max() / 10;

template<typename FROM, typename TO>
using umap = unordered_map<FROM, TO>;

struct edge {
    ll id;
    ll from;
    ll to;
    ll cap;
    ll cost;
    ll flow;

    edge(ll from, ll to) : from(from), to(to) {}

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
//    const ll INF = numeric_limits<ll>::max() / 10;


    solve(vt<vt<vt<ll>>> &dp, vt<vert> &tmp, ll id, ll p_color, ll color, ll k) {
        size = tmp[id].edges.size() + 1 + k + 2;
        s = size - 2;
        t = size - 1;
        dist = vt<ll>(size, INF);
        dist[s] = 0;
        parent = vt<edge *>(size);
        for (int i = 0; i < size; ++i) {
            G.emplace_back(i);
        }
        for (int i = 1; i <= tmp[id].edges.size(); ++i) {
            for (int j = 0; j < k; ++j) {
                add_edge(i, tmp[id].edges.size() + 1 + j, 1, dp[tmp[id].edges[i - 1].to][j][color]);
            }
        }
        add_edge(0, tmp[id].edges.size() + 1 + p_color, 1, 0);
        for (int i = 0; i < tmp[id].edges.size() + 1; ++i) {
            add_edge(s, i, 1, 0);
        }
        for (int i = tmp[id].edges.size() + 1; i < s; ++i) {
            add_edge(i, t, 1, 0);
        }
        for (int i = 0; i < size; ++i) {
            for (auto &p : G[i].edges) {
                edge *real = &p;
                auto tmp1 = edges_info.find(real->id ^ 1ll);
                edge *fake = &G[tmp1->second.first].edges[tmp1->second.second];
                redge.insert({real, fake});
            }
        }
    }

    solve(vt<vt<vt<ll>>> &dp, vt<vert> &tmp, ll id, ll color, ll k) {
        size = tmp[id].edges.size() + k + 2;
        s = size - 2;
        t = size - 1;
        dist = vt<ll>(size, INF);
        dist[s] = 0;
        parent = vt<edge *>(size);
        for (int i = 0; i < size; ++i) {
            G.emplace_back(i);
        }
        for (int i = 0; i < tmp[id].edges.size(); ++i) {
            for (int j = 0; j < k; ++j) {
                add_edge(i, tmp[id].edges.size() + j, 1, dp[tmp[id].edges[i].to][j][color]);
            }
        }
        for (int i = 0; i < tmp[id].edges.size(); ++i) {
            add_edge(s, i, 1, 0);
        }
        for (int i = tmp[id].edges.size(); i < s; ++i) {
            add_edge(i, t, 1, 0);
        }

        for (int i = 0; i < size; ++i) {
            for (auto &p : G[i].edges) {
                edge *real = &p;
                auto tmp1 = edges_info.find(real->id ^ 1ll);
                edge *fake = &G[tmp1->second.first].edges[tmp1->second.second];
                redge.insert({real, fake});
            }
        }
    }

    void add_edge(ll from, ll to, ll cap, ll cost) {
        edge real = edge(from, to, cap, cost);
        edge fake = edge(to, from, 0, -cost);
        edges_info.insert({real.id, {from, G[from].edges.size()}});
        edges_info.insert({fake.id, {to, G[to].edges.size()}});
        G[from].edges.push_back(real);
        G[to].edges.push_back(fake);
    }

    ll find_min_cost_flow() {
        ll answer = 0;
//        potentials = init_potentials();
        potentials = vt<ll>(size, 0);
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

struct hungarian {
    ll n;
    ll m;
    vt<ll> u, v, p, way;
    vt<vt<ll>> a;

    hungarian(const hungarian& o): n(o.n), m(o.m), u(o.u), v(o.v), p(o.p), way(o.way), a(o.a){}

    hungarian(vt<vert> &G, vt<vt<vt<ll>>> &dp, ll id, ll k, ll color) : n(G[id].edges.size()), m(k) {
        u = vt<ll>(n + 2);
        v = vt<ll>(m + 1);
        p = vt<ll>(m + 1);
        way = vt<ll>(m + 1);
        a = vt<vt<ll>>(n + 1, vt<ll>(m + 1, 0ll));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                a[i][j] = dp[G[id].edges[i - 1].to][j - 1][color];
            }
        }
    }

    ll min_cost() {
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            ll j0 = 0;
            vector<ll> minv(m + 1, INF);
            vector<bool> used(m + 1, false);
            do {
                used[j0] = true;
                ll i0 = p[j0], delta = INF, j1 = 0;
                for (int j = 1; j <= m; ++j)
                    if (!used[j]) {
                        ll cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j])
                            minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j], j1 = j;
                    }
                for (int j = 0; j <= m; ++j)
                    if (used[j])
                        u[p[j]] += delta, v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                ll j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        return -v[0];
    }

    ll add_line_and_count(ll color_p) {
        a.push_back(vt<ll>(m + 1, INF));
        a[a.size() - 1][0] = 0;
        a[a.size() - 1][color_p + 1] = 0;
        ll i = n + 1;
        p[0] = i;
        ll j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<bool> used(m + 1, false);
        do {
            used[j0] = true;
            ll i0 = p[j0], delta = INF, j1 = 0;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    ll cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            ll j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
        return -v[0];
    }
};

struct solution {
    ll n;
    ll k;
    ll p;
    ll max_depth;
    vt<vert> G;
    vt<vt<vt<ll>>> dp;
    vt<vt<ll>> price;
    vt<ll> depths;

    solution(ll n, ll k, ll p) : n(n), k(k), p(p) {
        dp = vt<vt<vt<ll>>>(n, vt<vt<ll>>(k, vt<ll>(k, INF)));
        price = vt<vt<ll>>(n, vt<ll>(k));
        depths = vt<ll>(n);
    }

    ll solvee() {
        read_graph();
        vt<ll> deq;
        for (int i = 0; i < n; ++i) {
            deq.emplace_back(i);
        }
        sort(deq.begin(), deq.end(), [this](ll a, ll b) { return depths[a] < depths[b]; });
        for (ll i : deq) {
            if (depths[i] == max_depth) {
                for (int j = 0; j < k; ++j) {
                    for (int l = 0; l < k; ++l) {
                        dp[i][j][l] = price[i][j];
                    }
                }
            }
        }
        while (deq.back() == max_depth)
            deq.pop_back();

        while (deq.size() > 1) {
//            cout << "------\n";
//            cout.flush();
            ll i = deq.back();
            deq.pop_back();
            for (int color = 0; color < k; ++color) {
                ll sum = 0;
                for (edge &e : G[i].edges) {
                    ll minimum = INF;
                    for (int ch_color = 0; ch_color < k; ++ch_color) {
                        minimum = min(minimum, dp[e.to][ch_color][color]);
                    }
                    sum += minimum;
                }
                for (int par_color = 0; par_color < k; ++par_color) {
                    dp[i][color][par_color] = p + price[i][color] + sum;
                }
            }
            if (G[i].edges.size() + 1 > k)
                continue;

            for (int color = 0; color < k; ++color) {
                hungarian hung(G, dp, i, k, color);
                hung.min_cost();
                for (int p_color = 0; p_color < k; ++p_color) {
                    hungarian copy(hung);
                    dp[i][color][p_color] = min(dp[i][color][p_color], copy.add_line_and_count(p_color) + price[i][color]);
                }
            }
        }
        if (n > 1) {
            ll i = deq.back();
            deq.pop_back();
            for (int color = 0; color < k; ++color) {
                ll sum = 0;
                for (edge &e : G[i].edges) {
                    ll minimum = INF;
                    for (int ch_color = 0; ch_color < k; ++ch_color) {
                        minimum = min(minimum, dp[e.to][ch_color][color]);
                    }
                    sum += minimum;
                }
                for (int par_color = 0; par_color < k; ++par_color) {
                    dp[i][color][par_color] = p + price[i][color] + sum;
                }
            }
            if (G[i].edges.size() <= k) {
                for (int color = 0; color < k; ++color) {
                    hungarian hung(G, dp, i, k, color);
                    dp[i][color][0] = min(dp[i][color][0], hung.min_cost() + price[i][color]);
                }
            }
        }
        //answer
        ll answer = INF;
        for (int color = 0; color < k; ++color) {
            answer = min(answer, dp[0][color][0]);
        }
        return answer;
    }

    void read_graph() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                cin >> price[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            G.emplace_back(i);
        }

        for (int i = 0; i < n - 1; ++i) {
            ll from;
            ll to;
            cin >> from >> to;
            from--;
            to--;
            G[from].edges.emplace_back(from, to);
            G[to].edges.emplace_back(to, from);
        }
        max_depth = 0;
        dfs(0, 0);
    }

    void dfs(ll v, ll depth) {
        G[v].is_visited = true;
        depths[v] = depth;
        max_depth = max(depth, max_depth);
        vt<edge> new_edges;
        for (edge &e : G[v].edges) {
            if (!G[e.to].is_visited) {
                new_edges.push_back(e);
                dfs(e.to, depth + 1);
            }
        }
        G[v].edges = new_edges;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    ifstream fin("assignment.in");
//    ofstream fout("assignment.out");

    ll n, k, p;
    cin >> n >> k >> p;
    solution sol(n, k, p);
//    sol.read_graph();
    cout << sol.solvee() << '\n';
    return 0;
}