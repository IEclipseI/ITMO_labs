//
// Created by Роман on 25.04.2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct triple {
    triple() : x(0), y(0), number(0) {}

    triple(int x, int y, int number) : x(x), y(y), number(number) {}

    int x;
    int y;
    int number;
};

struct node {
    explicit node(triple value) : value(value) {}

    triple value;
    node *parent = nullptr;
    node *left = nullptr;
    node *right = nullptr;
};


int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int x;
    int y;
    vector<triple> vect(n);
    for (int i = 0; i < n; ++i) {
        cin >> vect[i].x >> vect[i].y;
        vect[i].number = i;
    }

    sort(vect.begin(), vect.end(), [](triple const &a, triple const &b) {
        return a.x < b.x;
    });
    ran
    vector<node *> node_adr(n);
    auto *previous = new node(vect[0]);
    node_adr[previous->value.number] = previous;
    for (int i = 1; i < n; ++i) {
        auto *tmp = new node(vect[i]);
        while (previous->parent != nullptr && previous->value.y > tmp->value.y) {
            previous = previous->parent;
        }
        if (previous->parent == nullptr) {
            if (previous->value.y > tmp->value.y) {
                tmp->left = previous;
                previous->parent = tmp;
            } else {
                if (previous->right != nullptr) {
                    previous->right->parent = tmp;
                    tmp->left = previous->right;
                }
                previous->right = tmp;
                tmp->parent = previous;
            }
        } else {
            if (previous->right != nullptr) {
                previous->right->parent = tmp;
                tmp->left = previous->right;
            }
            previous->right = tmp;
            tmp->parent = previous;
        }
        previous = tmp;
        node_adr[previous->value.number] = previous;
    }
    cout << "YES" << endl;
    for (int i = 0; i < n; ++i) {
        cout << (node_adr[i]->parent ? node_adr[i]->parent->value.number + 1: 0)
             << " " << (node_adr[i]->left?node_adr[i]->left->value.number + 1:0)
             << " " << (node_adr[i]->right?node_adr[i]->right->value.number + 1:0) << endl;
    }

    return 0;
}