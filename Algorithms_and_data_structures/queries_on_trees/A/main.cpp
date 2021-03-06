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

ui get_lca(ui a, ui b, vec<ui> &depth, vec<vec<ui>> &dp, ui log_n, ui n) {
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

int main() {
  ios_base::sync_with_stdio(false);
  ui n;
  cin >> n;
  ui log_n = static_cast<ui>(ceil(log(static_cast<double> (n)) / log(2)));
  vec<vec<ui>> dp(n + 1, vec<ui>(log_n));
  for (int i = 0; i < log_n; ++i) {
    dp[1][i] = 1;
  }
  vec<ui> depth(n + 1);
  depth[1] = 0;
  for (size_t i = 2; i <= n; ++i) {
    ui tmp;
    cin >> tmp;
    dp[i][0] = tmp;
    for (int j = 1; j < log_n; ++j) {
      dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
    depth[i] = depth[tmp] + 1;
  }
  ui m;
  cin >> m;
  for (size_t i = 0; i < m; ++i) {
    ui a, b;
    cin >> a >> b;
    cout << get_lca(a, b, depth, dp, log_n - 1, n) << endl;
  }
  return 0;
}