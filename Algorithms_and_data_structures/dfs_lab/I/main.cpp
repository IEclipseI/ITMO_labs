#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <fstream>
#include <list>
#include <cmath>
#include <iomanip>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

struct vertex {
    vertex(ui id, double weigth, ui end_id) : id(id), weight(weigth), end_id(end_id) {}

    ui id = 0;
    double weight = 0;
    ui end_id = 0;
};

struct point {
    ui x;
    ui y;
};

double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    std::ios_base::sync_with_stdio(false);
//    ifstream fin("avia.in");
//    ofstream fout("avia.out");
//    fin.tie(nullptr);
    ui n;
    cin >> n;
    vec<point> points(n);
    for (ui i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }
//    vec<vec<double>> gr(n, vec<double>(n));
//    for (size_t i = 0; i < n; ++i) {
//        for (size_t j = 0; j < n; ++j) {
//            gr[i][j] = dist(points[i], points[j]);
//        }
//    }
    list<vertex> left;
    for (ui i = 1; i < n; ++i) {
        left.emplace_back(i, dist(points[0], points[i]), 0);
    }
    double answer = 0;
    for (ui i = 1; i < n; ++i) {
        vertex min = left.begin().operator*();
        auto min_it = left.begin();
        for (auto it = left.begin(); it != left.end(); it++) {
            if (min.weight > it.operator*().weight) {
                min = it.operator*();
                min_it = it;
            }
        }
        left.erase(min_it);
        answer += min.weight;
        for (vertex &v : left) {
            if (v.weight > dist(points[v.id], points[min.id])) {
                v.weight = dist(points[v.id], points[min.id]);
                v.end_id = min.id;
            }
        }
    }
    cout <<setprecision(15) <<answer << '\n';

    return 0;
}
