//
// Created by Роман on 23.05.2018.
//

#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

vec<ui> lca_h;
vec<ui> lca_dfs_list;
vec<ui> lca_first;
vec<ui> lca_tree;


ui depths_and_times(vec<vec<ui>> &nodes,
                    vec<ui> &depths,
                    ui root,
                    int parent_depth,
                    vec<ui> &times, ui time) {
  depths[root] = parent_depth;
  times[root] = time;
  for (ui kid : nodes[root]) {
    time = depths_and_times(nodes, depths, kid, parent_depth + 1, times, time + 1);
  }
  return time;
}

void lca_dfs(vec<vec<ui>> &nodes, ui v, ui h) {
  lca_h[v] = h;
  lca_dfs_list.push_back(v);
  for (vector<ui>::const_iterator i = nodes[v].begin(); i != nodes[v].end(); ++i) {
    lca_dfs(nodes, *i, h + 1);
    lca_dfs_list.push_back(v);
  }
}

void lca_build_tree(int i, int l, int r) {
  if (l == r)
    lca_tree[i] = lca_dfs_list[l];
  else {
    int m = (l + r) >> 1;
    lca_build_tree(i + i, l, m);
    lca_build_tree(i + i + 1, m + 1, r);
    if (lca_h[lca_tree[i + i]] < lca_h[lca_tree[i + i + 1]])
      lca_tree[i] = lca_tree[i + i];
    else
      lca_tree[i] = lca_tree[i + i + 1];
  }
}

void lca_prepare(vec<vec<ui>> &nodes,
                 ui root) {
  int n = (int) nodes.size();
  lca_h.resize(n);
  lca_dfs_list.reserve(n * 2);

  lca_dfs(nodes, root, 1);

  int m = (int) lca_dfs_list.size();
  lca_tree.assign(lca_dfs_list.size() * 4 + 1, -1);
  lca_build_tree(1, 0, m - 1);

  lca_first.assign(n, -1);
  for (int i = 0; i < m; ++i) {
    int v = lca_dfs_list[i];
    if (lca_first[v] == -1)
      lca_first[v] = i;
  }
}

int lca_tree_min(int i, int sl, int sr, int l, int r) {
  if (sl == l && sr == r)
    return lca_tree[i];
  int sm = (sl + sr) >> 1;
  if (r <= sm)
    return lca_tree_min(i + i, sl, sm, l, r);
  if (l > sm)
    return lca_tree_min(i + i + 1, sm + 1, sr, l, r);
  int ans1 = lca_tree_min(i + i, sl, sm, l, sm);
  int ans2 = lca_tree_min(i + i + 1, sm + 1, sr, sm + 1, r);
  return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca(int a, int b) {
  int left = lca_first[a],
      right = lca_first[b];
  if (left > right) std::swap(left, right);
  return lca_tree_min(1, 0, (int) lca_dfs_list.size() - 1, left, right);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ui n;
  cin >> n;
  vec<vec<ui>> nodes(n + 1);
  ui root = 0;
  for (ui i = 1; i <= n; ++i) {
    int parent;
    cin >> parent;
    if (parent == -1) {
      root = i;
      parent = 0;
    }
    nodes[parent].push_back(i);
  }
  vec<ui> depths(n + 1);
  vec<ui> times(n + 1);
  depths_and_times(nodes, depths, root, 0, times, 0);
  ui m;
  cin >> m;
  lca_prepare(nodes, root);
  vec<ui> set(n + 2);
  for (size_t i = 0; i < m; ++i) {
    ui k;
    cin >> k;
    set[0] = root;
    for (size_t j = 1; j <= k; ++j) {
      cin >> set[j] ;
    }
    std::sort(set.begin(), set.begin() + k + 1, [&times](ui l, ui r) {
      return times[l] < times[r];
    });
    ui answer = 1;
    for (size_t j = 1; j <= k; ++j) {
      ui lca_value = lca(set[j - 1], set[j]);
      answer += depths[set[j]] - depths[lca_value];
    }
    cout << answer << '\n';
  }
  return 0;
}