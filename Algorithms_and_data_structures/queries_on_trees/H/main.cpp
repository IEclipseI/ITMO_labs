//
// Created by Роман on 20.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

struct node {
  int sum = 1;
  ui color;
  vec<ui> kids;
};

ui get_lca(ui a, ui b, vec<ui> &depth, vec<vec<ui>> &dp, ui log_n) {
  if (depth[a] != depth[b]) {
    if (depth[a] < depth[b]) {
      swap(a, b);
    }
    ui log_tmp = log_n;
    while (depth[a] != depth[b]) {
      if (depth[dp[a][log_tmp]] >= depth[b]) {
        a = dp[a][log_tmp];
      }
      log_tmp--;
    }
  }
  if (a == b) {
    return a;
  }
  int log_tmp = log_n;
  while (log_tmp >= 0) {
    if (dp[a][log_tmp] != dp[b][log_tmp]) {
      a = dp[a][log_tmp];
      b = dp[b][log_tmp];
    }
    log_tmp--;
  }
  return dp[a][0];
}

void dfs(vec<node> &nodes, vec<ui> &last, ui v, ui log_n, vec<vec<ui>>& dp, vec<ui> &depth) {
  for (ui kid : nodes[v].kids) {
    dfs(nodes, last, kid, log_n, dp, depth);
    nodes[v].sum += nodes[kid].sum;
  }
  if (last[nodes[v].color] != 0) {
    nodes[get_lca(v, last[nodes[v].color], depth, dp, log_n)].sum--;
  }
  last[nodes[v].color] = v;
}

void make_like_A(ui log_n, ui v, ui root, vec<node> &nodes, vec<vec<ui>> &dp, vec<ui> &depth) {
  dp[v][0] = root;
  for (int j = 1; j < log_n; ++j) {
    dp[v][j] = dp[dp[v][j - 1]][j - 1];
  }
  depth[v] = depth[root] + 1;
  for (ui kid : nodes[v].kids) {
    make_like_A(log_n, kid, v, nodes, dp, depth);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  ui n;
  cin >> n;
  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }
  ui root;
  vec<node> nodes(n + 1);
  for (size_t i = 1; i <= n; ++i) {
    ui p;
    cin >> p;
    nodes[p].kids.push_back(i);
    cin >> nodes[i].color;
    if (p == 0) {
      root = i;
    }
  }
  vec<ui> last(n + 1);
  ui log_n = static_cast<ui>(ceil(log(static_cast<double> (n)) / log(2)));
  vec<vec<ui>> dp(n + 1, vec<ui>(log_n));
  for (int i = 0; i < log_n; ++i) {
    dp[root][i] = root;
  }
  vec<ui> depth(n + 1);
  depth[root] = UINT32_MAX;
  make_like_A(log_n, root, root, nodes, dp, depth);
  dfs(nodes, last, root, log_n - 1, dp, depth);
  for (int i = 1; i <=n; ++i) {
    cout << nodes[i].sum << " ";
  }
  cout << endl;
  return 0;
}