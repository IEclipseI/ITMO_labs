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

int get_min(ui a, ui lca, vec<ui> &depth, vec<vec<ui>> &dp, vec<vec<int>> &price, ui log_n, ui n, vec<ui> &pows_2) {
  int ans = INT32_MAX;
  ui delta = depth[a] - depth[lca];
  ui log_tmp = log_n;
  while(delta != 0) {
    if (pows_2[log_tmp] <= delta) {
      delta -= pows_2[log_tmp];
      ans = min(ans, price[a][log_tmp]);
      a = dp[a][log_tmp];
    }
    log_tmp--;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  ifstream fin("minonpath.in");
  ofstream fout("minonpath.out");
  ui n;
  fin >> n;
  ui log_n = static_cast<ui>(ceil(log(static_cast<double> (n)) / log(2)));
  vector<ui> pows_2(log_n);
  if (n != 1) pows_2[0] = 1;
  for (size_t i = 1; i < log_n; ++i) {
    pows_2[i] = pows_2[i - 1] * 2;
  }
  vec<vec<ui>> dp(n + 1, vec<ui>(log_n));
  vec<vec<int>> price(n + 1, vec<int>(log_n));
  for (int i = 0; i < log_n; ++i) {
    dp[1][i] = 1;
    price[1][i] = INT32_MAX;
  }
  vec<ui> depth(n + 1);
  depth[1] = 0;
  for (size_t i = 2; i <= n; ++i) {
    ui tmp;
    int local_min;
    fin >> tmp >> local_min;
    dp[i][0] = tmp;
    price[i][0] = local_min;
    for (int j = 1; j < log_n; ++j) {
      dp[i][j] = dp[dp[i][j - 1]][j - 1];
      price[i][j] = std::min(price[dp[i][j - 1]][j - 1], price[i][j - 1]);
    }
    depth[i] = depth[tmp] + 1;
  }
  ui m;
  fin >> m;
  for (size_t i = 0; i < m; ++i) {
    ui a, b;
    fin >> a >> b;
    ui lca = get_lca(a, b, depth, dp, log_n - 1, n);
    fout << min(get_min(a, lca, depth, dp, price, log_n - 1, n, pows_2), get_min(b, lca, depth, dp, price, log_n - 1, n, pows_2)) << endl;
  }
  return 0;
}