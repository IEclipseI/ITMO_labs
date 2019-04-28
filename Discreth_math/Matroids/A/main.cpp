#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;
template<class T>
        using vec = vector<T>;
using ll = int64_t;

struct task {
    ll d = 0, w = 0;
};

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("schedule.in");
    ofstream fout("schedule.out");
    fin.tie(nullptr);

    int n;
    fin >> n;
    vec<task> tasks(static_cast<unsigned int>(n));
    ll max_d = 0;
    for (int i = 0; i < n; ++i) {
        fin >> tasks[i].d >> tasks[i].w;
        max_d = max(max_d, tasks[i].d);
    }
    sort(tasks.begin(), tasks.end(), [](const task&  a, const task & b){ return a.w > b.w;});
    auto b = tasks.begin();
    auto e = b;
    while (e != tasks.end() && e->w == b->w){
        e++;
    }
    while (e != tasks.end()){
        stable_sort(b, e, [](const task&  a, const task & b){ return a.d > b.d;});
        b = e;
        while (e != tasks.end() && e->w == b->w){
            e++;
        }
    }
    set<ll> time{};
    for (int i = 0; i < n; ++i) {
        time.insert(i);
    }

    if (max_d > 0) {
        ll answer = 0;
        for (int i = 0; i < n; ++i) {
            auto next = time.lower_bound(tasks[i].d);
            if (next == time.begin()) {
                answer += tasks[i].w;
                continue;
            } else {
                next--;
                time.erase(next);
            }
        }
        fout << answer << "\n";
    } else {
        ll answer = 0;
        for (int i = 0; i < n; ++i) {
            answer += tasks[i].w;
        }
        fout << answer << "\n";
    }
    return 0;
}