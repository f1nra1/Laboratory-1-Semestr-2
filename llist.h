#ifndef LLIST_H
#define LLIST_H
#include <string>
using namespace std;

struct LNode {
    string data;
    LNode* pNext;
    LNode* pPrev;
};

struct LList {
    int size;
    LNode* head;
    LNode* tail;
};

void CreateLList(LList* llist);
LNode* CreateLNode(string data);
void LPushHead(LList* llist, string data);
void LPushTail(LList* llist, string data);
void LPushBefore(LList* llist, string data, string element);
void LPushAfter(LList* llist, string data, string element);
void LPopHead(LList* llist);
void LPopTail(LList* llist);
void LPopElement(LList* llist, string element);
bool LSearch(LList* llist, string element);
void PrintLList(LList* llist);
void DestroyLList(LList* llist);

#endif