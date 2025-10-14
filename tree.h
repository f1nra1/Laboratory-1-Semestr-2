#ifndef TREE_H
#define TREE_H
#include <string>
using namespace std;

struct TNode {
    string data;
    TNode* left;
    TNode* right;
};

struct BinaryTree {
    TNode* root;
    int size;
};

void CreateTree(BinaryTree* tree);
TNode* CreateNode(string data);
void TPush(BinaryTree* tree, string data);
bool TSearch(BinaryTree* tree, string data);
bool isComplete(BinaryTree* tree);
void PrintTree(TNode* root);
void preOrder(TNode* node);
void inOrder(TNode* node);
void postOrder(TNode* node);
void DestroyTree(TNode* node);

#endif