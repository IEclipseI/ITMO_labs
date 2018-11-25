//
// Created by Роман on 14.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
typedef uint32_t ui;

void checkForGood(uint32_t n,
                  vector<vector<vector<ui>>> &reverseMoves,
                  vector<bool> &terminal,
                  vector<bool> &good,
                  vector<bool> &visited,
                  vector<bool> &connected) {
    if (visited[n]) {
        return;
    }
    visited[n] = true;
    if (!connected[n]) {
        good[n] = false;
        return;
    }
    good[n] = true;
    for (int i = 0; i < 26; ++i) {
        for (ui t : reverseMoves[n][i]) {
            checkForGood(t, reverseMoves, terminal, good, visited, connected);
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

    uint32_t n, m, k;
    fin >> n >> m >> k;
    vector<vector<uint32_t>> moves(n + 1, vector<uint32_t>(26));
    vector<vector<vector<ui>>> reverseMoves(n + 1, vector<vector<ui>>(26));
    vector<bool> terminal(n + 1);
    for (int i = 0; i < k; ++i) {
        uint32_t t;
        fin >> t;
        terminal[t] = true;
    }
    for (int i = 0; i < m; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        moves[a][c - 'a'] = b;
        reverseMoves[b][c - 'a'].push_back(a);
    }
    vector<bool> vis1(n + 1);
    vector<bool> connected(n + 1);
    checkConnection(1, connected, moves, vis1);
    vis1 = vector<bool>(n+ 1);
    vector<bool> good(n + 1);
    for (int i = 0; i <= n; ++i) {
        if (terminal[i]) {
            checkForGood(i, reverseMoves, terminal, good, vis1, connected);
        }
    }
    if (connected[0]) {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (moves[i][j] == 0 && connected[i])
                    reverseMoves[0][j].push_back(i);
            }
        }
    }
    vector<vector<bool>> marked(n + 1, vector<bool>(n + 1, false));
    queue<pair<ui, ui>> q;
    for (ui i = 0; i <= n; ++i) {
        for (ui j = 0; j <= n; ++j) {
            if (!marked[i][j] && (terminal[i] != terminal[j])) {
                marked[i][j] = (marked[j][i] = true);
                q.push(pair<ui, ui>(i, j));
            }
        }
    }
    while (!q.empty()) {
        pair<ui, ui> p = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            for (ui s : reverseMoves[p.first][i]) {
                for (ui t : reverseMoves[p.second][i]) {
                    if (!marked[s][t]) {
                        marked[s][t] = (marked[t][s] = true);
                        q.push(pair<ui, ui>(s, t));
                    }
                }
            }
        }
    }
    vector<int> component(n + 1, -1);
    for (int i = 0; i <= n; ++i) {
        if (!marked[0][i]) {
            component[i] = 0;
        }
    }
    ui componentNumber = 0;
    for (int i = 1; i <= n; ++i) {
        if (!connected[i]) {
            continue;
        }
        if (component[i] == -1) {
            componentNumber++;
            component[i] = componentNumber;
            for (int j = i + 1; j <= n; ++j) {
                if (!marked[i][j]) {
                    component[j] = componentNumber;
                }
            }
        }
    }
    fout << componentNumber << " ";
    vector<vector<ui>> new_moves(componentNumber + 1, vector<ui>(26));
    for (ui i = 1; i <= n; ++i) {
        for (ui j = 0; j < 26; ++j) {
            if (good[i] && moves[i][j] != 0 && component[i] >= 1 && component[i] <= componentNumber) {
                new_moves[component[i]][j] = component[moves[i][j]];
            }
        }
    }
    ui numbers_of_moves = 0;
    for (int i = 1; i <= componentNumber; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (new_moves[i][j] != 0) {
                numbers_of_moves++;
            }
        }
    }
    fout << numbers_of_moves << " ";
    vector<bool> new_terminal(componentNumber + 1);
    for (int i = 1; i <= n; ++i) {
        if (terminal[i] && good[i]) {
            new_terminal[component[i]] = true;
        }
    }
    ui term = 0;
    for (int i = 1; i <= componentNumber; ++i) {
        if (new_terminal[i]) {
            term++;
        }
    }
    fout << term << endl;
    for (int i = 1; i <= componentNumber; ++i) {
        if (new_terminal[i]) {
            fout << i << " ";
        }
    }
    fout << endl;
    for (int i = 1; i <= componentNumber; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (new_moves[i][j] != 0) {
                fout << i << " " << new_moves[i][j] << " " << (char) (j + 'a') << endl;
            }
        }
    }
    fout.close();
    return 0;
}