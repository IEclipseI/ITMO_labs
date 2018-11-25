//
// Created by Роман on 24.05.2018.
//

#include <vector>
#include <cstdint>
#include <ios>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

void add_dino(ui v, ui parent, vec<ui> &depths, vec<vec<ui>> &dp, vec<bool> &is_dead, vec<ui> &parents, ui log_n) {
  if (is_dead[parent]) {
    add_dino(v, parents[parent], depths, dp, is_dead, parents, log_n);
  }
  parents[v] = parent;
  depths[v] = depths[parent] + 1;
  dp[v][0] = parent;
  for (int i = 1; i < log_n; ++i) {
    dp[v][i] = dp[dp[v][i - 1]][i - 1];
  }
}

void kill_dino(ui v, vec<ui> &depths, vec<vec<ui>> &dp, vec<bool> &is_dead, vec<ui> &parents, ui log_n) {
  is_dead[v] = true;
}

ui nearest_undead(ui a, vec<ui> &parents, vec<bool> &is_dead) {
  if (is_dead[a]) {
    return nearest_undead(parents[a], parents, is_dead);
  }
  return a;
}

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

ui dino_lca(ui a, ui b, vec<ui> &depths, vec<vec<ui>> &dp, vec<bool> &is_dead, vec<ui> &parents, ui log_n){
  ui lca = get_lca(a, b, depths, dp, log_n - 1);
  if (is_dead[lca]) {
    return parents[lca] = nearest_undead(parents[lca], parents, is_dead);
  }
  return lca;
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ui n;
  cin >> n;
  ui log_n = static_cast<ui>(ceil(log(static_cast<double> (n)) / log(2)));
  vec<vec<ui>> dp(n + 1, vec<ui>(log_n));
  for (int i = 0; i < log_n; ++i) {
    dp[1][i] = 1;
  }
  vec<ui> depths(n + 1);
  vec<ui> parents(n + 1);
  vec<bool> is_dead(n + 1);
  char ch;
  ui dino_number = 2;
  for (int i = 0; i < n; ++i) {
    cin >> ch;
    if (ch ==  '+') {
      ui v;
      cin >> v;
      add_dino(dino_number, v, depths, dp, is_dead, parents, log_n);
      dino_number++;
    } else if (ch == '-') {
      ui v;
      cin >> v;
      kill_dino(v, depths, dp, is_dead, parents, log_n);
    } else {
      ui a, b;
      cin >> a >> b;
      cout << dino_lca(a, b ,depths, dp, is_dead, parents, log_n) << '\n';
    }
  }

  return 0;
}