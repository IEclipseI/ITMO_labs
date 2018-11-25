//
// Created by Роман on 08.04.2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
double S[100][100];

double difference(int *a, int *b, int n) {

    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    ifstream fin("markchain.in");
    ofstream fout("markchain.out");
    double *a = new double[100];
    double *b = new double[100];
    int n;
    fin >> n;
    int nn = n * n;
    a[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> S[i][j];
        }
    }
    double max_diff = 0;
    do {
        double s = 0;
        for (int j = 0; j < n; ++j) {
            b[j] = 0;
            for (int i = 0; i < n; ++i) {
                b[j] += a[i] * S[i][j];
            }
            s += b[j];
        }
        b[0] += 1 - s;
        max_diff = abs(b[0] - a[0]);
        for (int i = 0; i < n; ++i) {
            max_diff = max(abs(a[i] - b[i]), max_diff);
        }
        double *tmp = a;
        a = b;
        b = tmp;
    } while (max_diff > 0.00000005);

    for (int i = 0; i < n; ++i) {
        fout <<  (float)a[i] << endl;

    }
    fout.close();
    return 0;
}
