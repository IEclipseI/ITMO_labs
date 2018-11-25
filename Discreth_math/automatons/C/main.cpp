//
// Created by Роман on 25.04.2018.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;


uint64_t getRightAnswer(uint32_t n, vector<vector<uint32_t>> &moves, vector<bool> &terminal, vector<bool> &good) {
    uint64_t answer = terminal[n]?1:0;
    for (int i = 0; i < 26; ++i) {
        if (moves[n][i] != 0 && good[n]) {
            answer = (answer + getRightAnswer(moves[n][i], moves, terminal, good))% 1000000007;
        }
    }
    return answer;
}

void checkConnection(uint32_t n, vector<bool> &connected, vector<vector<uint32_t>> &moves, vector<bool> &visited) {
    if (visited[n]) {
        return;
    } else {
        visited[n] = true;
        connected[n] = true;
        for (int i = 0; i < 26; ++i) {
            if (moves[n][i] != 0) {
                checkConnection(moves[n][i], connected, moves, visited);
            }
        }
    }
}

void checkForGood(uint32_t n,
                  vector<vector<uint32_t>> &reverseMoves,
                  vector<bool> &terminal,
                  vector<bool> &good,
                  vector<bool> &visited) {
    if (visited[n]) {
        return;
    }
    visited[n] = true;
    good[n] = true;
    for (int i = 0; i < 26; ++i) {
        if (reverseMoves[n][i] != 0) {
            checkForGood(reverseMoves[n][i], reverseMoves, terminal, good, visited);
        }
    }
}

bool checkForEndless(uint32_t n,
                     vector<bool> &good,
                     vector<vector<uint32_t>> &moves,
                     vector<bool> &cycled, vector<bool> &visited) {
    if (visited[n]) {
        return false;
    }
    visited[n] = true;
    cycled[n] = true;
    bool result = false;
    for (int i = 0; i < 26; ++i) {
        if (moves[n][i] != 0) {
            if (good[moves[n][i]] && cycled[moves[n][i]]) {
                return true;
            }
            result = result || checkForEndless(moves[n][i], good, moves, cycled, visited);
            if (result) {
                return true;
            }
        }
    }
    cycled[n] = false;
    return result;
}

uint64_t count(uint32_t n, vector<vector<uint32_t>> &reverseMoves, vector<uint64_t> &answers, vector<bool> &visited) {
    if (visited[n]) {
        return answers[n];
    } else {
        uint64_t sum = 0;
        visited[n] = true;
        for (int i = 0; i < 26; ++i) {
            if (reverseMoves[n][i] != 0) {
                sum = (sum + count(reverseMoves[n][i], reverseMoves, answers, visited)) % 1000000007;
            }
        }
        answers[n] = sum;
        return sum;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("problem3.in");
    ofstream fout("problem3.out");
    uint32_t n, m, k;
    fin >> n >> m >> k;
//    if (n > 2) {
//        n = n / (n - n);
//    }
    vector<bool> terminal(n + 1);
    for (int i = 0; i < k; ++i) {
        uint32_t t;
        fin >> t;
        terminal[t] = true;
    }
    vector<vector<uint32_t>> moves(n + 1, vector<uint32_t>(26));
    vector<vector<uint32_t>> reverseMoves(n + 1, vector<uint32_t>(26));
    for (int i = 0; i < m; ++i) {
        uint32_t a, b;
        char c;
        fin >> a >> b >> c;
        moves[a][c - 'a'] = b;
        reverseMoves[b][c - 'a'] = a;
    }
    vector<bool> good(n + 1);
    vector<bool> visited(n + 1);
    for (uint32_t i = 1; i <= n; ++i) {
        if (terminal[i])
            checkForGood(i, reverseMoves, terminal, good, visited);
    }
    visited = vector<bool>(n + 1);
    vector<bool> cycled(n + 1);
    if (checkForEndless(1, good, moves, cycled, visited)) {
        fout << -1 << endl;
        fout.close();
        return 0;
    }
    vector<bool> connected(n + 1);
    visited = vector<bool>(n + 1);
    checkConnection(1, connected, moves, visited);
    visited = vector<bool>(n + 1);
    visited[1] = true;
    vector<uint64_t> answers(n + 1);
    answers[1] = 1;
    uint64_t answer = 0;
//    for (int i = 1; i <= n; ++i) {
//        if (terminal[i] && connected[i]) {
//            answer = (answer + count(i, reverseMoves, answers, visited)) % 1000000007;
//        }
//    }
    fout << getRightAnswer(1, moves, terminal, good) << endl;
    fout.close();
    return 0;
}
