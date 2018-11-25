#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct node {
    node() : sum(0), length(0), set(UINT32_MAX), left_border(0), right_border(0), left(0), right(0) {
    }

    uint32_t sum;
    uint32_t length;
    uint32_t set;
    uint32_t left_border;
    uint32_t right_border;
    uint32_t left;
    uint32_t right;

};

node tree[3000000];

void push(uint32_t node) {
    if (tree[node].set != UINT32_MAX) {
        tree[2 * node + 1].set = tree[node].set;
        tree[2 * node + 2].set = tree[node].set;
        tree[node].set = UINT32_MAX;
    }
}

pair<uint32_t, uint32_t> set(uint32_t node, uint32_t a, uint32_t b, uint32_t x) {
    if (tree[node].right < a || tree[node].left > b) {
        if (tree[node].set == UINT32_MAX) {
            return pair<uint32_t, uint32_t>(tree[node].sum, tree[node].length);
        }
        return pair<uint32_t, uint32_t>(tree[node].set, (tree[node].set *
                                                         (tree[node].right - tree[node].left + 1)));
    }
    if (tree[node].left >= a && tree[node].right <= b) {
        tree[node].set = x;
        return pair<uint32_t, uint32_t>(tree[node].set,
                                        (tree[node].set *
                                         (tree[node].right - tree[node].left + 1)));
    }
    push(node);
    pair<uint32_t, uint32_t> l(set(2 * node + 1, a, b, x));
    pair<uint32_t, uint32_t> r(set(2 * node + 2, a, b, x));
    pair<uint32_t, uint32_t> ans(l.first + r.first, l.second + r.second);
    tree[node].sum = (tree[2 * node + 1].set == UINT32_MAX ? tree[2 * node + 1].sum : tree[2 * node + 1].set) +
                     (tree[2 * node + 2].set == UINT32_MAX ? tree[2 * node + 2].sum : tree[2 * node + 2].set);
    tree[node].length = (tree[2 * node + 1].set == UINT32_MAX ? tree[2 * node + 1].length : (tree[2 * node + 1].set *
                                                                                             (tree[2 * node + 1].right -
                                                                                              tree[2 * node + 1].left +
                                                                                              1))) +
                        (tree[2 * node + 2].set == UINT32_MAX ? tree[2 * node + 2].length :
                         (tree[2 * node + 2].set * (tree[2 * node + 2].right - tree[2 * node + 2].left + 1)));
    tree[node].left_border =
            tree[2 * node + 1].set == UINT32_MAX ? tree[2 * node + 1].left_border : tree[2 * node + 1].set;
    tree[node].right_border =
            tree[2 * node + 2].set == UINT32_MAX ? tree[2 * node + 2].right_border : tree[2 * node + 2].set;

    if ((tree[2 * node + 1].set == UINT32_MAX ? tree[2 * node + 1].right_border : tree[2 * node + 1].set) == 1
        && (tree[2 * node + 2].set == UINT32_MAX ? tree[2 * node + 2].left_border : tree[2 * node + 2].set) == 1) {
        tree[node].sum--;
        ans.first--;
    }
    return ans;
}

uint32_t quest[100000][3];

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("painter.in");
    ofstream fout("painter.out");
    uint32_t n;
    fin >> n;
    uint32_t m = n;
    string str;
    int mov = 0;
    int maximum = 0;
    int a;
    int b;
    for (int i = 0; i < n; ++i) {
        fin >> str;
        if (str[0] == 'B') {
            quest[i][0] = 1;
        }
        fin >> a >> b;
        if (a < mov) {
            mov = a;
        }
        if (a + b > maximum) {
            maximum = a + b;
        }
        quest[i][1] = a;
        quest[i][2] = b;
    }

    int64_t size = ceil((double) log((double) maximum - mov) / log((double) 2));
    uint32_t length = pow(2, size);
    int64_t l = length * 2 - 1;
    n = maximum - mov;
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


//    std::cout << "----------" << '\n';
//    for (int64_t j = 0; j < length * 2 - 1; ++j) {
//        std::cout << ar[j] << '\n';
//    }
    for (int i = 0; i < m; ++i) {
        pair<uint32_t, uint32_t> ans(set(0, quest[i][1] - mov, quest[i][1] + quest[i][2] - mov - 1, quest[i][0]));
        fout << ans.first << " " << ans.second << endl;
    }

    fout.close();
    return 0;
}