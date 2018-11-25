//
// Created by Роман on 21.05.2018.
//

#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_set>

using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

void delete_extra(ui root, vec<unordered_set<ui>> &nodes) {
  for (ui kid : nodes[root]) {
    nodes[kid].erase(root);
    delete_extra(kid, nodes);
  }
}

ui dfs_for_subtree_sizes(ui root, vec<unordered_set<ui>> &nodes, vec<ui> &sizes) {
  sizes[root]++;
  for (ui kid : nodes[root]) {
    sizes[root] += dfs_for_subtree_sizes(kid, nodes, sizes);
  }
  return sizes[root];
}

void restore_parents(ui root, ui parent, vec<unordered_set<ui>> &new_nodes, vec<ui> &parents) {
  parents[root] = parent;
  for (ui kid : new_nodes[root]) {
    restore_parents(kid, root, new_nodes, parents);
  }
}

pair<ui, ui> find_centroid(ui root, ui parent, ui size_comp, vec<unordered_set<ui>> &nodes, vec<ui> &sizes) {
  for (ui kid : nodes[root]) {
    if (sizes[kid] > size_comp / 2) {
      pair<ui, ui> p(find_centroid(kid, root, size_comp, nodes, sizes));
      sizes[root]-=p.second;
      return p;
    }
  }
  nodes[parent].erase(root);
  return pair<ui, ui>(root, sizes[root]);
}

ui centroid_decomposition(vec<unordered_set<ui>> &nodes, ui cur_root, ui size_of_component, ui n, vec<ui> &sizes) {
  if (size_of_component < 3) {
    return cur_root;
  }
  ui centroid = find_centroid(cur_root, cur_root, size_of_component, nodes, sizes).first;
  unordered_set<ui> tmp;
  for (ui kid : nodes[centroid]) {
    tmp.insert(centroid_decomposition(nodes, kid, sizes[kid], n, sizes));
  }
  nodes[centroid] = tmp;
  if (centroid != cur_root) {
    nodes[centroid].insert(centroid_decomposition(nodes, cur_root, size_of_component - sizes[centroid], n, sizes));
  }
  return centroid;
}

int main() {
  ios::sync_with_stdio(false);
  ios_base::sync_with_stdio(false);
  ui n;
  cin >> n;
  vec<unordered_set<ui>> nodes(n + 1);
  vec<ui> parents(n + 1);
  for (int i = 1; i < n; ++i) {
    ui a, b;
    cin >> a >> b;
    nodes[a].insert(b);
    nodes[b].insert(a);
  }
  delete_extra(1, nodes);
  vec<ui> sizes(n + 1);
  dfs_for_subtree_sizes(1, nodes, sizes);
  ui root = centroid_decomposition(nodes, 1, n, n, sizes);
  restore_parents(root, 0, nodes, parents);
  for (int i = 1; i <= n; ++i) {
    cout << parents[i] << " ";
  }
  cout << endl;
  return 0;
}