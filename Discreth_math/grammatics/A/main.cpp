//
// Created by Роман on 24.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

int main() {
  ios_base::sync_with_stdio(false);

  ifstream fin("automaton.in");
  ofstream fout("automaton.out");
  fin.tie(nullptr);
  fout.tie(nullptr);

  ui n;
  fin >> n;
  char start;
  fin >> start;
  vec<vec<vec<ui>>> moves(27, vector<vec<ui>>(26));
  std::string word;
  char tmp;
  for (int i = 0; i < n; ++i) {
    fin >> tmp >> word;
    fin >> word;
    if (word.length() > 1) {
      moves[tmp - 'A'][word[0] - 'a'].push_back(word[1] - 'A');
    } else {
      moves[tmp - 'A'][word[0] - 'a'].push_back(26);
    }
  }
  ui m;
  fin >> m;
  for (int i = 0; i < m; ++i) {
    unordered_set<ui> cur_set{static_cast<unsigned int>(start - 'A')};
    unordered_set<ui> prev_set;
    fin >> word;
    for (int j = 0; j < word.length(); ++j) {
      std::swap(cur_set, prev_set);
      cur_set.clear();
      for (ui t : prev_set) {
        for (ui dest : moves[t][word[j] - 'a']) {
          cur_set.insert(dest);
        }
      }
    }
    if (cur_set.find(26) != cur_set.end()) {
      fout << "yes" << '\n';
    } else {
      fout << "no" << '\n';
    }
  }
  fout.close();
  return 0;
}
