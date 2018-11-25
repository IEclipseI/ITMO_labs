//
// Created by Роман on 08.04.2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    ifstream fin("shooter.in");
    ofstream fout("shooter.out");
    int k, n, m;
    fin >> n >> m >> k;
    long double p;
    long double sum = 0;
    for (int i = 0; i < k - 1; ++i) {
        fin >>  p;
        sum += pow(1 - p, m);
    }

    fin >> p;
    sum += pow(1 - p, m);
    long double general_p = 1 - p;
    for (int i = k; i < n; ++i) {
        fin >>  p;
        sum += pow(1 - p, m);
    }
    double ans= static_cast<double>(pow(general_p, m) / sum);
    fout <<setprecision(14) <<pow(general_p, m)/sum << endl;
    fout.close();
    return 0;
}
