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
  ifstream fin("epsilon.in");
  ofstream fout("epsilon.out");
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
  for (int i = 0; i < n; ++i) {
    getline(fin, rules[i]);
    if (rules[i].length() == 4) {
      set_of_eps_parent.insert(rules[i][0]);
    }
  }
//  set<char> good;
//  bool flag = true;
//  while (flag) {
//    flag = false;
//    for (int i = 0; i < n; ++i) {
//      bool fully_good = true;
//      for (int j = 5; j < rules[i].length(); ++j) {
//        if (good.find(rules[i][j]) == good.end()
//            && rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
//          fully_good = false;
//        }
//      }
//      if (fully_good && good.find(rules[i][0]) == good.end()) {
//        good.insert(rules[i][0]);
//        flag = true;
//      }
//    }
//  }
//
//  set<char> targeted{start};
//
//  flag = true;
//  while (flag) {
//    flag = false;
//    for (int i = 0; i < n; ++i) {
//      if (targeted.find(rules[i][0]) != targeted.end()) {
//        for (int j = 5; j < rules[i].length(); ++j) {
//          if (rules[i][j] >= 'A' && rules[i][j] <= 'Z' && targeted.find(rules[i][j]) == targeted.end()) {
//            flag = true;
//            targeted.insert(rules[i][j]);
//          }
//        }
//      }
//    }
//  }

  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < n; ++i) {
      bool fully_eps = true;
      for (int j = 5; j < rules[i].length(); ++j) {
        if (set_of_eps_parent.find(rules[i][j]) == set_of_eps_parent.end()) {
          fully_eps = false;
        }
      }
      if (fully_eps && set_of_eps_parent.find(rules[i][0]) == set_of_eps_parent.end()) {
        set_of_eps_parent.insert(rules[i][0]);
        flag = true;
      }
    }
  }

  set<char>::iterator it = set_of_eps_parent.begin();
  if (set_of_eps_parent.end() != it /*&& good.find(*it) != good.end() && targeted.find(*it) != targeted.end()*/) {
    fout << *it;
    it++;
  }
  while (it != set_of_eps_parent.end()) {
    /*if (good.find(*it) != good.end() && targeted.find(*it) != targeted.end()) */fout << " " << *it;
    it++;
  }
  fout.close();
  return 0;
}
