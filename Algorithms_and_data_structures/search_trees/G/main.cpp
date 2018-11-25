//
// Created by Роман on 25.04.2018.
//

#include <iostream>
#include <vector>

using namespace std;

struct treap {
    treap(int value, int y, int c):value(value), y(y), c(c), left(nullptr), right(nullptr){}
    int value;
    int y;
    int c;
    treap* left;
    treap* right;
};
int size(treap *t) {
    return t?t->c:0;
}

void recalc(treap* t) {
    if (!t) {
        return;
    }
    t->c = size(t->right) + 1;
}

treap* merge(treap* t1, treap* t2) {
    if (t2 == nullptr) return t1;
    if (t1 == nullptr) return t2;
    treap* answer;
    if (t1->y > t2->y) {
        t1->right = merge(t1->right, t2);
        answer = t1;
    } else {
        t2->left = merge(t1, t2->left);
        answer = t2;
    }
    recalc(answer);
    return answer;
}

pair<treap*, treap*> split(treap* t, int k) {
    if (t == nullptr) {
        return pair<treap*, treap*>(nullptr, nullptr);
    }
    int l = size(t->left);
    if (l >= k) {pair<treap*, treap*> p(split(t->left, k));
        t->left = p.second;
        recalc(t);
        return pair<treap*, treap*>(p.first, t);
    } else {
        pair<treap*, treap*> p(split(t->right, k - l - 1));
        t->right = p.first;
        recalc(t);
        return pair<treap*, treap*>(t, p.second);
    }
};

treap* insert(treap* t, int value, int i) {
    pair<treap*, treap*> p  = split(t, i);
    auto * node = new treap(value, rand(), i);
    return merge(merge(p.first, node), p.second);
}

void writeArray(treap* t) {
    if (t == nullptr) {
        return;
    }
    writeArray(t->left);
    cout << t->value << " ";
    writeArray(t->right);
}

int kElement(treap* t, int k) {
    while (t != nullptr) {
        int leftSize = size(t->left);
        if (leftSize == k) {
            return t->value;
        }
        t = leftSize > k? t->left: t->right;
        if (leftSize < k) {
            k-=leftSize + 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    treap* root = nullptr;
    int n;
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        root = insert(root, i + 1);
    }
    uint32_t l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        root = move(root, l, r);
    }
    writeArray(root);
//    root = insert(root, 5);
//    root = insert(root, 6);
//    root = insert(root, 7);
//    root = insert(root, 8);
//    root = insert(root, 9);
//    root = insert(root, 10);
//    root = insert(root, 11);
//    root = insert(root, 12);
//    root = insert(root, 13);
//    root = remove(root, 5);
//    root = remove(root, 13);
//    root = remove(root, 6);
//    root = remove(root, 12);
//    root = remove(root, 11);
//    root = remove(root, 7);
//    root = remove(root, 8);


    return 0;
}
