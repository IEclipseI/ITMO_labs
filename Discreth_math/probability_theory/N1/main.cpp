//
// Created by Роман on 08.04.2018.
//

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    ifstream fin("exam.in");
    ofstream fout("exam.out");
    int k, n;
    fin >> k >> n;
    uint32_t count, p;
    int64_t sum = 0;
    for (int i = 0; i < k; ++i) {
        fin >> count >> p;
        sum+=count*p;
    }
    double s = sum;
    s/=n*100;
    fout << s << endl;
    fout.close();
    return 0;
}
