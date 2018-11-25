#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct matrix {
    matrix(int64_t a, int64_t b, int64_t c, int64_t d) : a(a), b(b), c(c), d(d) {
    }

    int64_t a;
    int64_t b;
    int64_t c;
    int64_t d;
};

matrix mul_matrix(matrix f, matrix s, uint32_t r) {
    return matrix((f.a * s.a + f.b * s.c) % r,
                  (f.a * s.b + f.b * s.d) % r,
                  (f.c * s.a + f.d * s.c) % r,
                  (f.c * s.b + f.d * s.d) % r);
}

struct node {
    node() : mul(matrix(1, 0, 0, 1)), left(0), right(0) {
    }

    node(uint32_t left, uint32_t right) :
            mul(matrix(1, 0, 0, 1)),
            left(left),
            right(right) {
    }

    matrix mul;
    uint32_t left;
    uint32_t right;

};

node tree[800000];

matrix mul(uint32_t node, int64_t a, int64_t b, uint32_t r) {
    if (tree[node].right < a || tree[node].left > b) {
        return matrix(1, 0, 0, 1);
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return tree[node].mul;
    }
    return mul_matrix(mul(node * 2 + 1, a, b, r), mul(node * 2 + 2, a, b, r), r);
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("crypto.in");
    ofstream fout("crypto.out");
    uint32_t r, n, m;
    fin >> r >> n >> m;
    int64_t size = ceil((double) log((double) n) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t a = length * 2 - 1;
    for (uint32_t i = 0; i < n; ++i) {
        fin >> tree[length - 1 + i].mul.a >> tree[length - 1 + i].mul.b >> tree[length - 1 + i].mul.c
            >> tree[length - 1 + i].mul.d;
        tree[length - 1 + i].left = i + 1;
        tree[length - 1 + i].right = 1 + i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].left = 1 + i;
        tree[length - 1 + i].right = 1 + i;
    }
    for (int32_t i = length - 2; i >= 0; --i) {
        tree[i].mul = mul_matrix(tree[i * 2 + 1].mul, tree[i * 2 + 2].mul, r);
        tree[i].left = tree[2 * i + 1].left;
        tree[i].right = tree[2 * i + 2].right;
    }
    uint32_t left, right;
    for (int i = 0; i < m; ++i) {
        fin >> left >> right;
        matrix matr = mul(0, left, right, r);
        fout << matr.a << " " << matr.b << "\n" << matr.c << " " << matr.d << "\n\n";
    }
    fout.close();
    return 0;
}