#ifndef TREE_H
#define TREE_H
#include <string>
using namespace std;

struct TNode {
    string data;
    TNode* left;
    TNode* right;
    int height;
};

struct BinaryTree {
    TNode* root;
    int size;
};

void CreateTree(BinaryTree* tree);
void TPush(BinaryTree* tree, string data);
void TDelete(BinaryTree* tree, string data);
bool TSearch(BinaryTree* tree, string data);
void PrintTree(TNode* root);
void preOrder(TNode* node);
void inOrder(TNode* node);
void postOrder(TNode* node);
void DestroyTree(TNode* node);

#endif