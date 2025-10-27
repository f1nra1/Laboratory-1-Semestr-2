#include "tree.h"
#include "queue.h"
#include <iostream>
#include <algorithm>
using namespace std;

int getHeight(TNode* node) {
    return node ? node->height : 0;
}

void updateHeight(TNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

int getBalance(TNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

TNode* createNode(string data) {
    TNode* node = new TNode;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// Правый поворот
TNode* rotateRight(TNode* y) {
    TNode* x = y->left;
    TNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левый поворот
TNode* rotateLeft(TNode* x) {
    TNode* y = x->right;
    TNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Балансировка узла
TNode* balance(TNode* node) {
    if (!node) return nullptr;

    updateHeight(node);
    int bal = getBalance(node);

    // Left-Left
    if (bal > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left-Right
    if (bal > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Right
    if (bal < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right-Left
    if (bal < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Вставка узла
TNode* insertNode(TNode* node, string data, bool& inserted) {
    if (!node) {
        inserted = true;
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data, inserted);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data, inserted);
    } else {
        // Дубликат - не вставляем
        return node;
    }

    return balance(node);
}

// Найти минимальный узел
TNode* findMin(TNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Удаление узла
TNode* deleteNode(TNode* node, string data, bool& deleted) {
    if (!node) return nullptr;

    if (data < node->data) {
        node->left = deleteNode(node->left, data, deleted);
    } else if (data > node->data) {
        node->right = deleteNode(node->right, data, deleted);
    } else {
        deleted = true;

        // Узел с одним ребенком или без детей
        if (!node->left || !node->right) {
            TNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }

        // Узел с двумя детьми
        TNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data, deleted);
        deleted = true;
    }

    return balance(node);
}

// Публичные функции
void CreateTree(BinaryTree* tree) {
    tree->root = nullptr;
    tree->size = 0;
}

void TPush(BinaryTree* tree, string data) {
    bool inserted = false;
    tree->root = insertNode(tree->root, data, inserted);
    if (inserted) {
        tree->size++;
    }
}

void TDelete(BinaryTree* tree, string data) {
    bool deleted = false;
    tree->root = deleteNode(tree->root, data, deleted);
    if (deleted) {
        tree->size--;
    }
}

bool TSearch(BinaryTree* tree, string data) {
    TNode* current = tree->root;
    while (current) {
        if (data == current->data) {
            return true;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// Обход в ширину (level-order)
void PrintTree(TNode* root) {
    if (!root) {
        cout << "Дерево пустое" << endl;
        return;
    }

    Queue q;
    CreateQueue(&q);
    QPush(&q, to_string((long long)root));

    int level = 0;
    int nodesInLevel = 1;
    int nodesInNext = 0;

    cout << "Уровень " << level << ": ";

    while (q.size > 0) {
        string ptrStr = QPop(&q);
        TNode* current = (TNode*)(stoll(ptrStr));

        cout << current->data;
        nodesInLevel--;

        if (current->left) {
            QPush(&q, to_string((long long)current->left));
            nodesInNext++;
        }
        if (current->right) {
            QPush(&q, to_string((long long)current->right));
            nodesInNext++;
        }

        if (nodesInLevel > 0) {
            cout << " ";
        } else {
            cout << endl;
            if (nodesInNext > 0) {
                level++;
                cout << "Уровень " << level << ": ";
                nodesInLevel = nodesInNext;
                nodesInNext = 0;
            }
        }
    }

    DestroyQueue(&q);
}

// Прямой обход (Pre-order: корень -> левый -> правый)
void preOrder(TNode* node) {
    if (!node) return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

// Симметричный обход (In-order: левый -> корень -> правый)
void inOrder(TNode* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

// Обратный обход (Post-order: левый -> правый -> корень)
void postOrder(TNode* node) {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

// Уничтожение дерева
void DestroyTree(TNode* node) {
    if (!node) return;
    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}