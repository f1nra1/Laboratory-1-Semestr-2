#include "tree.h"
#include "queue.h"
#include <iostream>
#include <string>

TNode* CreateNode(string data) {
    TNode* newNode = new TNode;
    newNode -> data = data;
    newNode -> left = nullptr;
    newNode -> right = nullptr;
    return newNode;
}

void CreateTree(BinaryTree* tree) {
    tree -> root = nullptr;
    tree -> size = 0;
}

void TPush(BinaryTree* tree, string data) {
    if (!tree -> root) {
        tree -> root = CreateNode(data);
        tree -> size++;
        return;
    }

    Queue q;
    CreateQueue(&q);
    QPush(&q, to_string((long long)tree -> root));

    TNode* newNode = CreateNode(data);
    bool inserted = false;

    while (q.size > 0 && !inserted) {
        string ptrStr = QPop(&q);
        TNode* current = (TNode*)(stoll(ptrStr));

        if (!current -> left) {
            current -> left = newNode;
            inserted = true;
        } else if (!current -> right) {
            current -> right = newNode;
            inserted = true;
        } else {
            QPush(&q, to_string((long long)current -> left));
            QPush(&q, to_string((long long)current -> right));
        }
    }
    tree -> size++;
    DestroyQueue(&q);
}

bool TSearch(BinaryTree* tree, string data) {
    if (!tree -> root) return false;
    Queue q;
    CreateQueue(&q);
    QPush(&q, to_string((long long)tree -> root));

    while (q.size > 0) {
        string ptrStr = QPop(&q);
        TNode* current = (TNode*)(stoll(ptrStr));

        if (current -> data == data) {
            DestroyQueue(&q);
            return true;
        }
        if (current -> left) QPush(&q, to_string((long long)current -> left));
        if (current -> right) QPush(&q, to_string((long long)current -> right));
    }
    DestroyQueue(&q);
    return false;
}

bool isComplete(BinaryTree* tree) {
    if (!tree -> root) return true;

    Queue q;
    CreateQueue(&q);
    QPush(&q, to_string((long long)tree -> root));

    bool nullFound = false;

    while (q.size > 0) {
        string ptrStr = QPop(&q);
        TNode* current = (TNode*)(stoll(ptrStr));

        if (current -> left) {
            if (nullFound) {
                DestroyQueue(&q);
                return false;
            }
            QPush(&q, to_string((long long)current -> left));
        } else {
            nullFound = true;
        }

        if (current -> right) {
            if (nullFound) {
                DestroyQueue(&q);
                return false;
            }
            QPush(&q, to_string((long long)current -> right));
        } else {
            nullFound = true;
        }
    }

    DestroyQueue(&q);
    return true;
}

void PrintTree(TNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }

    Queue q;
    CreateQueue(&q);
    QPush(&q, to_string((long long)root));

    int level = 0;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    cout << "Level " << level << ": [";

    while (q.size > 0) {
        string ptrStr = QPop(&q);
        TNode* current = (TNode*)(stoll(ptrStr));

        cout << current -> data;
        nodesInCurrentLevel--;

        if (current -> left) {
            QPush(&q, to_string((long long)current -> left));
            nodesInNextLevel++;
        }
        if (current -> right) {
            QPush(&q, to_string((long long)current -> right));
            nodesInNextLevel++;
        }

        if (nodesInCurrentLevel > 0) {
            cout << ", ";
        } else {
            cout << "]" << endl;
            if (nodesInNextLevel > 0) {
                level++;
                cout << "Level " << level << ": [";
                nodesInCurrentLevel = nodesInNextLevel;
                nodesInNextLevel = 0;
            }
        }
    }
    DestroyQueue(&q);
}

void preOrder(TNode* node) {
    if (!node) return;
    cout << node -> data << " ";
    preOrder(node -> left);
    preOrder(node -> right);
}

void inOrder(TNode* node) {
    if (!node) return;
    inOrder(node -> left);
    cout << node -> data << " ";
    inOrder(node -> right);
}

void postOrder(TNode* node) {
    if (!node) return;
    postOrder(node -> left);
    postOrder(node -> right);
    cout << node -> data << " ";
}

void DestroyTree(TNode* node) {
    if (!node) return;
    DestroyTree(node -> left);
    DestroyTree(node -> right);
    delete node;
}