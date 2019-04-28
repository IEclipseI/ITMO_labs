#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename T>
using vt = vector<T>;

using ll = int64_t;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("rps2.in");
    ofstream fout("rps2.out");
    ll r1, s1, p1, r2, s2, p2;
    fin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
    ll zero = 0; //wtf, why it does not compile without that
    fout << max(max(r1 - r2 - p2, max(p1 - p2 - s2 , s1 - s2 - r2)), zero);
    return 0;
}