//
// Created by Роман on 25.04.2018.
//

#include <iostream>
#include <vector>

using namespace std;

struct treap {
    treap(uint64_t x, int y) : x(x), y(y), sum(x), left(nullptr), right(nullptr) {}

    uint64_t x;
    int y;
    uint64_t sum;
    treap *left;
    treap *right;
};

uint64_t size(treap *t) {
    return t ? t->sum : 0;
}

void recalc(treap *t) {
    if (!t) {
        return;
    }
    t->sum = size(t->left) + size(t->right) + t->x;
}

treap *merge(treap *t1, treap *t2) {
    if (t2 == nullptr) return t1;
    if (t1 == nullptr) return t2;
    treap *answer;
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

pair<treap *, treap *> split(treap *t, uint64_t k) {
    if (t == nullptr) {
        return pair<treap *, treap *>(nullptr, nullptr);
    }
    if (k > t->x) {
        pair<treap *, treap *> p(split(t->right, k));
        t->right = p.first;
        recalc(t);
        return pair<treap *, treap *>(t, p.second);
    } else {
        pair<treap *, treap *> p(split(t->left, k));
        t->left = p.second;
        recalc(t);
        return pair<treap *, treap *>(p.first, t);
    }
};

treap *insert(treap *t, uint64_t x) {
    pair<treap *, treap *> p = split(t, x);
    auto *node = new treap(x, rand());
    return merge(merge(p.first, node), split(p.second, x + 1).second);
}

treap *remove(treap *t, uint64_t x) {
    pair<treap *, treap *> p = split(t, x);
    return merge(p.first, split(p.second, x + uint64_t(1)).second);
}

uint64_t summary(treap *t, uint64_t l, uint64_t r) {
    pair<treap *, treap *> p1 = split(t, l);
    pair<treap *, treap *> p2 = split(p1.second, r + 1);
    uint64_t ans = p2.first?p2.first->sum:0;
    merge(merge(p1.first, p2.first), p2.second);
    return ans;
}

int kElement(treap *t, int k) {
    while (t != nullptr) {
        int leftSize = size(t->left);
        if (leftSize == k) {
            return t->x;
        }
        t = leftSize > k ? t->left : t->right;
        if (leftSize < k) {
            k -= leftSize + 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    treap *root = nullptr;
    char command;
    uint64_t value;
    int n;
    cin >> n;
    bool flag = false;
    uint64_t previousAnswer = 0;
    for (int i = 0; i < n; ++i) {
        cin >> command >> value;
        if (command == '+') {
            if (flag) {
                root = insert(root, (value + previousAnswer) % 1000000000);
                flag = false;
            } else {
                root = insert(root, value);
            }
        } else {
            uint64_t l = value, r;
            cin >> r;
            uint64_t ans = summary(root, l, r);
            previousAnswer = ans;
            flag = true;
            cout << ans << endl;
        }
    }
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
