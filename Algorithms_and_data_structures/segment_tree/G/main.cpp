#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    node() : max(0), add(0), left(0), right(0) {
    }

    int32_t max;
    int32_t add;
    uint32_t left;
    uint32_t right;

};

struct dote {
    dote(int32_t x, int32_t y_up, int32_t y_bottom, int32_t value) : x(x), y_up(y_up), y_bottom(y_bottom),
                                                                     value(value) {}
    int32_t x;
    int32_t y_up;
    int32_t y_bottom;
    int32_t value;
};

node tree[1600000];

void push(uint32_t node) {
    tree[2 * node + 1].add += tree[node].add;
    tree[2 * node + 2].add += tree[node].add;
    tree[node].add = 0;
}


int32_t maximum(uint32_t node, uint32_t a, uint32_t b) {
    if (tree[node].right < a || tree[node].left > b) {
        return INT32_MIN;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        return tree[node].max + tree[node].add;
    }
    push(node);
    int32_t ans = max(maximum(2 * node + 1, a, b), maximum(2 * node + 2, a, b));
    tree[node].max = max(tree[2 * node + 1].max + tree[2 * node + 1].add,
                         tree[2 * node + 2].max + tree[2 * node + 2].add);
    return ans;
}

void add(uint32_t node, uint32_t a, uint32_t b, int32_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        return;
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].add += x;
        return;
    }
    push(node);
    add(2 * node + 1, a, b, x);
    add(2 * node + 2, a, b, x);
    tree[node].max = max(tree[2 * node + 1].max + tree[2 * node + 1].add,
                         tree[2 * node + 2].max + tree[2 * node + 2].add);
}

uint32_t search_y(uint32_t node, int32_t m) {
    if (tree[node].left == tree[node].right) {
        return tree[node].right;
    }
    push(node);
    int32_t l = tree[2 * node + 1].max + tree[2 * node + 1].add;
    int32_t ans;
    if (l == m) {
        ans = search_y(2 * node + 1, m);
    } else {
        ans = search_y(2 * node + 2, m);
    }
    tree[node].max = max(l, tree[2 * node + 2].max + tree[2 * node + 2].add);

}

bool comp1(dote a, dote b) {
    return a.x < b.x;
}
bool comp2(dote a, dote b) {
    return a.value > b.value && a.x == b.x || a.x < b.x;
}

int main() {
    ios::sync_with_stdio(false);
    uint32_t n;
    cin >> n;
    uint32_t m = n;
    string str;
    int mov = 0;
    int maximum_y = 0;
    vector<dote> line;
    for (int i = 0; i < n; ++i) {
        int32_t x1;
        int32_t x2;
        int32_t y1;
        int32_t y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y2 > maximum_y) {
            maximum_y = y2;
        }
        if (y1 < mov) {
            mov = y1;
        }
        dote tmp (x1, y2, y1, 1);
        line.push_back(tmp);
        tmp = dote(x2, y2, y1, -1);
        line.push_back(tmp);
    }
    stable_sort(line.begin(), line.end(), comp1);
    stable_sort(line.begin(), line.end(), comp2);

    int64_t size = ceil((double) log((double) maximum_y - mov + 1) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t l = length * 2 - 1;
    n = maximum_y - mov + 1;
    for (uint32_t i = 0; i < n; ++i) {
        tree[length - 1 + i].left = i;
        tree[length - 1 + i].right = i;
    }
    for (uint32_t i = n; i < length; ++i) {
        tree[length - 1 + i].left = i;
        tree[length - 1 + i].right = i;
    }
    for (int32_t j = length - 2; j >= 0; --j) {
        tree[j].left = tree[2 * j + 1].left;
        tree[j].right = tree[2 * j + 2].right;
    }

    int32_t answer = 0;
    int32_t answer_x = 0;
    int32_t answer_y = 0;
    for (dote t : line) {
        add(0, t.y_bottom - mov, t.y_up - mov, t.value);
        int32_t tmp_answer = maximum(0 , 0 , n);
        if (tmp_answer > answer) {
            answer = tmp_answer;
            answer_x = t.x;
            answer_y = search_y(0, answer) + mov;
        }
    }
    cout << answer <<endl << answer_x << " "<<answer_y <<endl;
//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
//    for (int i = 0; i < m; ++i) {
//        pair<uint32_t, uint32_t> ans(set(0, quest[i][1] - mov, quest[i][1] + quest[i][2] - mov - 1, quest[i][0]));
//        fout << ans.first << " " << ans.second << endl;
//    }

    return 0;
}