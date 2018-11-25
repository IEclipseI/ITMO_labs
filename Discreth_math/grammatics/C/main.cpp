//
// Created by Роман on 24.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

typedef uint32_t ui;

template<typename T>
using vec = std::vector<T>;

int main() {
  ios_base::sync_with_stdio(false);
  ifstream fin("useless.in");
  ofstream fout("useless.out");
  fin.tie(nullptr);
  fout.tie(nullptr);
  ui n;
  fin >> n;
  char start;
  fin >> start;
  std::string word;
  set<char> set_of_eps_parent;
  getline(fin, word);
  vec<string> rules(n);
  set<char> cur{start};
  for (int i = 0; i < n; ++i) {
    getline(fin, rules[i]);
    if (rules[i].length() == 4) {
      set_of_eps_parent.insert(rules[i][0]);
    }
    for (int j = 0; j < rules[i].length(); ++j) {
      cur.insert(rules[i][j]);
    }
  }
  set<char> good;
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < n; ++i) {
      bool fully_good = true;
      for (int j = 5; j < rules[i].length(); ++j) {
        if (good.find(rules[i][j]) == good.end()
            && rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
          fully_good = false;
        }
      }
      if (fully_good && good.find(rules[i][0]) == good.end()) {
        good.insert(rules[i][0]);
        flag = true;
      }
    }
  }
  vec<string> new_rules;
  for (int i = 0; i < n; ++i) {
    bool tmp = true;
    for (int j = 5; j < rules[i].length(); ++j) {
      if (good.find(rules[i][j]) == good.end() && rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
        tmp = false;
        break;
      }
    }
    if (!tmp) continue;
    new_rules.push_back(rules[i]);
  }
  set<char> targeted{start};

  flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < new_rules.size(); ++i) {
      if (targeted.find(new_rules[i][0]) != targeted.end()) {
        for (int j = 5; j < new_rules[i].length(); ++j) {
          if (new_rules[i][j] >= 'A' && new_rules[i][j] <= 'Z' && targeted.find(new_rules[i][j]) == targeted.end()) {
            flag = true;
            targeted.insert(new_rules[i][j]);
          }
        }
      }
    }
  }

  set<char> usefull;
  for (int i = 0; i < new_rules.size(); ++i) {
    if (targeted.find(new_rules[i][0]) != targeted.end()) {
      usefull.insert(new_rules[i][0]);
    }
  }
  bool first = true;
  for (int i = 0; i <= 25; ++i) {
    if (usefull.find(static_cast<char>('A' + i)) == usefull.end() && cur.find(static_cast<char>('A' + i)) != cur.end()) {
      if (first) {
        fout << static_cast<char>('A' + i);
        first = false;
      } else {
        fout << " " << static_cast<char>('A' + i);
      }
    }
  }
  fout.close();
  return 0;
}
