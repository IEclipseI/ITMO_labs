//
// Created by Роман on 21.05.2018.
//

#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <fstream>

using namespace std;

typedef uint32_t ui;

struct node {
  int64_t value = 0;
  ui left = 0;
  ui right = 0;
  int64_t add = 0;
};

template<typename T>
using vec = std::vector<T>;

void delete_extra(ui root, vec<vec<ui>> &nodes, vec<vec<ui>> &new_nodes, vec<bool> &visited) {
  visited[root] = true;
  for (ui kid : nodes[root]) {
    if (!visited[kid]) {
      new_nodes[root].push_back(kid);
      delete_extra(kid, nodes, new_nodes, visited);
    }
  }
}

ui dfs_for_subtree_sizes(ui root, vec<vec<ui>> &nodes, vec<ui> &sizes) {
  sizes[root]++;
  for (ui kid : nodes[root]) {
    sizes[root] += dfs_for_subtree_sizes(kid, nodes, sizes);
  }
  return sizes[root];
}

void create_set_of_paths(ui root, vec<vec<ui>> &paths, ui index, vec<vec<ui>> &nodes, vec<ui> &sizes) {
  paths[index].push_back(root);
  ui biggest = 0;
  for (ui kid : nodes[root]) {
    if (sizes[kid] > sizes[biggest]) {
      biggest = kid;
    }
  }
  for (ui kid : nodes[root]) {
    if (kid != biggest) {
      paths.push_back(vec<ui>());
      create_set_of_paths(kid, paths, paths.size() - 1, nodes, sizes);
    } else {
      create_set_of_paths(biggest, paths, index, nodes, sizes);
    }
  }
}

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

void get_depths_and_parents(vec<ui> &parents, vec<ui> &depth, vec<vec<ui>> &nodes, ui root, ui cur_depth, ui parent) {
  depth[root] = cur_depth;
  parents[root] = parent;
  for (ui kid : nodes[root]) {
    get_depths_and_parents(parents, depth, nodes, kid, cur_depth + 1, root);
  }
}

void set_tree(vec<node> &tree, ui l, ui r, ui root, int64_t change) {
  if (tree[root].left > r || tree[root].right < l) {
    return;
  }
  if (tree[root].left >= l && tree[root].right <= r) {
    tree[root].value = change;
    return;
  }
  set_tree(tree, l, r, root * 2 + 1, change);
  set_tree(tree, l, r, root * 2 + 2, change);
  tree[root].value = std::max(tree[root * 2 + 1].value, tree[root * 2 + 2].value);
}

int64_t get_max_value(vec<node> &tree, ui l, ui r, ui root) {
  if (tree[root].left > r || tree[root].right < l) {
    return 0;
  }
  if (tree[root].left >= l && tree[root].right <= r) {
    return tree[root].value;
  }
  return std::max(get_max_value(tree, l, r, root * 2 + 1),get_max_value(tree, l, r, root * 2 + 2));
}

void build_dp(vec<vec<ui>> &nodes, vec<vec<ui>> &dp, ui parent, ui root, ui log_n) {
  dp[root][0] = parent;
  for (ui j = 1; j < log_n; ++j) {
    dp[root][j] = dp[dp[root][j - 1]][j - 1];
  }
  for (ui kid : nodes[root]) {
    build_dp(nodes, dp, root, kid, log_n);
  }
}

int64_t max_on_path(ui lca,
                    ui cur_number,
                    vec<vec<ui>> &paths,
                    vec<ui> &number_in_DO,
                    vec<ui> &number_of_DO,
                    vec<vec<node>> &DO,
                    vec<ui> &parents,
                    int64_t change) {
  int64_t answer = 0;
  if (number_of_DO[lca] != number_of_DO[cur_number]) {
    answer = get_max_value(DO[number_of_DO[cur_number]], 0, number_in_DO[cur_number], 0);
    answer = std::max(answer,  max_on_path(lca,
                                           parents[paths[number_of_DO[cur_number]][0]],
                                           paths,
                                           number_in_DO,
                                           number_of_DO,
                                           DO,
                                           parents,
                                           change));
  } else {
    answer = get_max_value(DO[number_of_DO[cur_number]], number_in_DO[lca], number_in_DO[cur_number], 0);
  }
  return answer;
}

int main() {
  ios_base::sync_with_stdio(false);
  ifstream fin("mail.in");
  ofstream fout("mail.out");
  ui n;
  fin >> n;
  vec<ui> default_high(n + 1);
  for (int i = 1; i <= n; ++i) {
    fin >> default_high[i];
  }
  if (n == 1) {
    int64_t value = default_high[1];
    ui m;
    fin >> m;
    char ch;
    for (int i = 0; i < m; ++i) {
      fin >> ch;
      if (ch == '?') {
        fin >> n;
        fin >> n;
        fout << value << endl;
      } else {
        fin >> n;
        fin >> n;
        value = n;
      }
    }
    return 0;
  }
  vec<vec<ui>> nodes(n + 1);
  for (int i = 1; i < n; ++i) {
    ui a, b;
    fin >> a >> b;
    nodes[a].push_back(b);
    nodes[b].push_back(a);
  }
  vec<vec<ui>> new_nodes(n + 1);
  vec<bool> visited(n + 1);
  delete_extra(1, nodes, new_nodes, visited);

  std::swap(nodes, new_nodes);
  vec<ui> sizes(n + 1);
  vec<ui> depths(n + 1);
  vec<ui> parents(n + 1);
  get_depths_and_parents(parents, depths, nodes, 1, 0, 0);
  dfs_for_subtree_sizes(1, nodes, sizes);

  vec<vec<ui>> paths;
  paths.push_back(vector<ui>());
  create_set_of_paths(1, paths, 0, nodes, sizes);

  vec<ui> number_of_DO(n + 1);
  vec<ui> number_in_DO(n + 1);
  for (ui i = 0; i < paths.size(); ++i) {
    for (ui j = 0; j < paths[i].size(); ++j) {
      number_of_DO[paths[i][j]] = i;
      number_in_DO[paths[i][j]] = j;
    }
  }
  vec<vec<node>> DO;
  for (int i = 0; i < paths.size(); ++i) {
    ui length = pow(2, ceil(log(paths[i].size()) / log(2)));
    DO.push_back(vector<node>(length * 2 - 1));
    for (ui j = 0; j < paths[i].size(); ++j) {
      DO[i][length - 1 + j].left = j;
      DO[i][length - 1 + j].right = j;
      DO[i][length - 1 + j].value = default_high[paths[i][j]];
    }
    for (ui j = paths[i].size(); j < length; ++j) {
      DO[i][length - 1 + j].left = j;
      DO[i][length - 1 + j].right = j;
    }
    for (int j = length - 2; j >= 0; --j) {
      DO.back()[j].left = DO.back()[j * 2 + 1].left;
      DO.back()[j].right = DO.back()[j * 2 + 2].right;
      DO.back()[j].value = std::max(DO.back()[j * 2 + 2].value , DO.back()[j * 2 + 1].value);
    }
  }

  ui log_n = static_cast<ui>(ceil(log(static_cast<double> (n)) / log(2)));
  vec<vec<ui>> dp(n + 1, vec<ui>(log_n));
  for (int i = 0; i < log_n; ++i) {
    dp[1][i] = 1;
  }
  build_dp(nodes, dp, 1, 1, log_n);

  ui m;
  fin >> m;
  char ch;
  for (int i = 0; i < m; ++i) {
    fin >> ch;
    if (ch == '!') {
      ui number, h;
      fin >> number >> h;
      set_tree(DO[number_of_DO[number]], number_in_DO[number], number_in_DO[number], 0, h);
    } else {
      ui a, b;
      fin >> a >> b;
      ui lca = get_lca(a, b, depths, dp, log_n - 1, n);
      if (lca != a && lca != b) {
        fout << std::max(max_on_path(lca, a, paths, number_in_DO, number_of_DO, DO, parents, 0),
                         max_on_path(lca, b, paths, number_in_DO, number_of_DO, DO, parents, 0))<< endl;
      } else {
        fout << max_on_path(lca, a == lca ? b : a, paths, number_in_DO, number_of_DO, DO, parents, 0) << endl;
      }
    }
  }
  return 0;
}