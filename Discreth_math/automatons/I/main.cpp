//
// Created by Роман on 15.05.2018.
//

#include <cstdint>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;
typedef uint32_t ui;

void check_for_useful(uint32_t n,
                      vector<vector<vector<ui>>> &reverseMoves,
                      vector<bool> &useful,
                      vector<bool> &visited) {
    if (visited[n]) {
        return;
    }
    visited[n] = true;
    useful[n] = true;
    for (int i = 0; i < 26; ++i) {
        for (ui t : reverseMoves[n][i]) {
            check_for_useful(t, reverseMoves, useful, visited);
        }
    }
}

void checkConnection(uint32_t n, vector<bool> &connected, vector<vector<uint32_t>> &moves, vector<bool> &visited) {
    if (visited[n]) {
        return;
    } else {
        visited[n] = true;
        connected[n] = true;
        for (int i = 0; i < 26; ++i) {
            checkConnection(moves[n][i], connected, moves, visited);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("fastminimization.in");
    ofstream fout("fastminimization.out");
    ui n, m, k;
    fin >> n >> m >> k;
    vector<ui> good_points;
    good_points.push_back(0);
    vector<bool> terminal(n + 1);
    for (int i = 0; i < k; ++i) {
        ui t;
        fin >> t;
        terminal[t] = true;
    }

    vector<vector<ui>> moves(n + 1, vector<ui>(26));
    vector<vector<vector<ui>>> reverse_moves(n + 1, vector<vector<ui>>(26));
    for (int i = 0; i < m; ++i) {
        ui a, b;
        char c;
        fin >> a >> b >> c;
        reverse_moves[b][c - 'a'].push_back(a);
        moves[a][c - 'a'] = b;
    }

    vector<bool> visited(n + 1);
    vector<bool> connected(n + 1);
    checkConnection(1, connected, moves, visited);

    vector<bool> useful(n + 1);
    visited = vector<bool>(n + 1);
    for (ui i = 1; i <= n; ++i) {
        if (terminal[i]) {
            check_for_useful(i, reverse_moves, useful, visited);
        }
    }
    vector<ui> biection(n + 1);
    for (ui i = 1; i <= n; ++i) {
        if (connected[i] && useful[i]) {
            biection[i] = good_points.size();
            good_points.push_back(i);
        }
    }
    vector<vector<ui>> good_moves(good_points.size(), vector<ui>(26));
    vector<vector<vector<ui>>> good_reverse_moves(good_points.size(), vector<vector<ui>>(26));
    for (ui i = 1; i < good_points.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (useful[moves[good_points[i]][j]]) {
                good_moves[i][j] = biection[moves[good_points[i]][j]];
                good_reverse_moves[biection[moves[good_points[i]][j]]][j].push_back(i);
            }
        }
    }
    vector<bool> good_terminal(good_points.size());
    for (int i = 1; i < good_points.size(); ++i) {
        if (terminal[good_points[i]]) {
            good_terminal[biection[good_points[i]]] = true;
        }
    }
    n = good_points.size();
    if (n == 1) {
        fout << 0 <<" "<< 0 <<" "<< 0<< endl;
        return 0;
    }
    vector<unordered_set<ui>> P;
    vector<ui> Class(n);
    queue<pair<ui, ui>> Queue;
    unordered_set<ui> tmp1;
    for (ui i = 1; i < n; ++i) {
        if (good_terminal[i]) {
            Class[i] = 0;
            tmp1.insert(i);
        }
    }
    if (!tmp1.empty()) {
        P.push_back(tmp1);
    } /*else {
        fout << 0 << " " << 0 << " " << 0 << endl;
        return 0;
    }*/
    unordered_set<ui> tmp2;
    for (ui i = 1; i < n; ++i) {
        if (!good_terminal[i]) {
            Class[i] = 1;
            tmp2.insert(i);
        }
    }
    if (!tmp2.empty()) {
        P.push_back(tmp2);
    }
    for (ui i = 0; i < 26; ++i) {
        if (!tmp1.empty()) {
            Queue.push(pair<ui, ui>(0, i));
        }
        if (!tmp2.empty()) {
            Queue.push(pair<ui, ui>(1, i));
        }
    }
    while (!Queue.empty()) {
        pair<ui, ui> para = Queue.front();
        Queue.pop();
        unordered_map<ui, vector<ui>> Involved;
        for (ui q: P[para.first]) {
            for (ui r : good_reverse_moves[q][para.second]) {
                ui i = Class[r];
                if (Involved.find(i) == Involved.end()) {
                    Involved.insert(pair<ui, vector<ui>>(i, vector<ui>()));
                }
                Involved.find(i).operator*().second.push_back(r);
            }
        }
        for (pair<ui, vector<ui>> part : Involved) {
            if (part.second.size() < P[part.first].size()) {
                P.push_back(unordered_set<ui>());
                ui j = P.size() - 1;
                for (ui r : part.second) {
                    P[part.first].erase(r);
                    P[j].insert(r);
                }
                if (P[j].size() > P[part.first].size()) {
                    swap(P[j], P[part.first]);
                }
                for (ui r : P[j]) {
                    Class[r] = j;
                }
                for (ui i = 0; i < 26; ++i) {
                    Queue.push(pair<ui, ui>(j, i));
                }
            }
        }
    }
    for (ui i = 0; i < P.size(); ++i) {
        for(ui t : P[i]) {
            Class[t] = i;
        }
    }
    if (Class[1] != 0) {
        ui s = Class[1];
        for (ui t : P[0]) {
            Class[t] = s;
        }
        for (ui t : P[s]) {
            Class[t] = 0;
        }
        swap(P[0], P[s]);
    }
    ui number_of_points = P.size();
    fout << number_of_points << " ";
    vector<bool> finally_terminal(number_of_points);
    ui number_of_terminal = 0;
    vector<ui> vector_of_terminal;
    for (ui i = 0; i < number_of_points; ++i) {
        for (ui t : P[i]) {
            if (good_terminal[t]) {
                finally_terminal[i] = true;
                vector_of_terminal.push_back(i);
                number_of_terminal++;
                break;
            }
        }
    }
    vector<vector<int>> final_moves(number_of_points, vector<int>(26, -1));
    for (ui i = 0; i < number_of_points; ++i) {
        for (ui t : P[i]) {
            for (int j = 0; j < 26; ++j) {
                if (good_moves[t][j] != 0) {
                    final_moves[i][j] = Class[good_moves[t][j]];
                }
            }
        }
    }
    ui number_of_moves = 0;
    for (int i = 0; i < number_of_points; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (final_moves[i][j] != -1) {
                number_of_moves++;
            }
        }
    }
    fout <<number_of_moves << " " << number_of_terminal << endl;
    for (ui t  : vector_of_terminal) {
        fout << t + 1<< " ";
    }
    fout << endl;
    for (int i = 0; i < number_of_points; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (final_moves[i][j] != -1) {
                fout << i + 1 << " " <<final_moves[i][j] + 1 << " " << (char)('a' + j)<< endl;
            }
        }
    }
    fout.close();
    return 0;
}