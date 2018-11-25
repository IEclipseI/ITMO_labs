//
// Created by Роман on 08.04.2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
int bi[100002];

int main() {
    std::ios::sync_with_stdio(false);
    ifstream fin("lottery.in");
    ofstream fout("lottery.out");
    int n, m;
    fin >> n >> m;
    long double p = 1;
    bi[0] = 0;
    int k;
    long double sum = 0;
    int previous_win = 0;
    int win;

    for (int i = 0; i < m; ++i) {
        fin >> k >> win;
        sum += (((p)) - (p/=k)) * previous_win;
        previous_win = win;
    }
    sum  += win * p;
    fout <<setprecision(14) << n - sum << endl;
    fout.close();
    return 0;
}
