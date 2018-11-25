//
// Created by Роман on 22.04.2018.
//
#include <iostream>

using namespace std;

struct node {
    explicit node(int32_t x) : key(x) {}

    int32_t diff = 0;
    int32_t height = 1;
    int32_t key;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
};

node *tree = nullptr;

void balance(node *a);

void rotateLeft(node *a);

void rotateBigLeft(node *a);

void rotateRight(node *a);

void rotateBigRight(node *a);

int32_t getHeight(node *node) {
    return node ? node->height : 0;
}

node *prev(node *root, int32_t x) {
    node *successor = nullptr;
    while (root != nullptr) {
        if (root->key < x) {
            successor = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return successor;
}

node *next(node *root, int32_t x) {
    node *successor = nullptr;
    while (root != nullptr) {
        if (root->key > x) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return successor;
}
void recalcNode(node *node) {
    if (node == nullptr) {
        return;
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node->diff = getHeight(node->left) - getHeight(node->right);
}

void insert(node *root, int32_t x) {
    if (root == nullptr) {
        tree = new node(x);
        return;
    }
    if (root->key == x) {
        return;
    }
    if (root->key > x) {
        if (root->left == nullptr) {
            root->left = new node(x);
            root->left->parent = root;
            balance(root->left);
            recalcNode(root);
        } else {
            insert(root->left, x);
        }
    } else {
        if (root->right == nullptr) {
            root->right = new node(x);
            root->right->parent = root;
            balance(root->right);
            recalcNode(root);
        } else {
            insert(root->right, x);
        }
    }
}

void balance(node *a) {
    if (a == nullptr) {
        return;
    }
    recalcNode(a);
    if (a->diff == -2) {
        if (a->right->diff == 1) {
            rotateBigLeft(a);
        } else {
            rotateLeft(a);
        }
    }
    if (a->diff == 2) {
        if (a->left->diff == -1) {
            rotateBigRight(a);
        } else {
            rotateRight(a);
        }
    }
    recalcNode(a);
    balance(a->parent);
}

void rotateBigRight(node *a) {
    rotateLeft(a->left);
    rotateRight(a);
}

void rotateRight(node *a) {
    node *b = a->left;
    a->left = b->right;
    if (b->right != nullptr) {
        b->right->parent = a;
    }
    b->right = a;
    if (a->parent == nullptr) {
        tree = b;
        b->parent = nullptr;
    } else {
        if (a->parent->left == a) {
            a->parent->left = b;
        } else {
            a->parent->right = b;
        }
        b->parent = a->parent;
    }
    a->parent = b;
    recalcNode(a);
    recalcNode(b);
}

void rotateBigLeft(node *a) {
    rotateRight(a->right);
    rotateLeft(a);
}

void rotateLeft(node *a) {
    node *b = a->right;
    a->right = b->left;
    if (b->left != nullptr) {
        b->left->parent = a;
    }
    b->left = a;
    if (a->parent == nullptr) {
        tree = b;
        b->parent = nullptr;
    } else {
        if (a->parent->left == a) {
            a->parent->left = b;
        } else {
            a->parent->right = b;
        }
        b->parent = a->parent;
    }
    a->parent = b;
    recalcNode(a);
    recalcNode(b);
}

void remove(node *root, int32_t x) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        if (root->parent == nullptr) {
            tree = nullptr;
            return;
        }
        if (root == root->parent->right) {
            root->parent->right = nullptr;
        } else {
            root->parent->left = nullptr;
        }
        balance(root->parent);
        return;
    }
    if (root->left != nullptr && root->right != nullptr) {
        node *next_node = next(root->right, x);
        root->key = next_node->key;
        remove(next_node, x);
        return;
    }
    if (root->left != nullptr) {
        if (root->parent == nullptr) {
            tree = root->left;
            root->left->parent = nullptr;
            return;
        }
        if (root == root->parent->right) {
            root->parent->right = root->left;
            root->left->parent = root->parent;
        } else {
            root->parent->left = root->left;
            root->left->parent = root->parent;
        }
    } else {
        if (root->parent == nullptr) {
            tree = root->right;
            root->right->parent = nullptr;
            return;
        }
        if (root == root->parent->right) {
            root->parent->right = root->right;
            root->right->parent = root->parent;
        } else {
            root->parent->left = root->right;
            root->right->parent = root->parent;
        }
    }
    balance(root->parent);
}

node *find(node *root, int32_t x) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key == x) {
        return root;
    }
    if (root->key > x) {
        return find(root->left, x);
    } else {
        return find(root->right, x);
    }
}

bool exist(node *root, int32_t x) {
    return static_cast<bool>(find(root, x));
}

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    int32_t x;
    while (cin >> s) {
        cin >> x;
        if (s[0] == 'i') {
            insert(tree, x);
        } else if (s[0] == 'e') {
            if (exist(tree, x)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        } else if (s[0] == 'n') {
            node *tmp = next(tree, x);
            if (tmp) {
                cout << tmp->key << endl;
            } else {
                cout << "none" << endl;
            }
        } else if (s[0] == 'p') {
            node *tmp = prev(tree, x);
            if (tmp) {
                cout << tmp->key << endl;
            } else {
                cout << "none" << endl;
            }
        } else {
            remove(find(tree, x), x);
        }
    }
    return 0;
}