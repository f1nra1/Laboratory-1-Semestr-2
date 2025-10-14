#ifndef FLIST_H
#define FLIST_H
#include <string>
using namespace std;

struct FNode {
    string data;
    FNode* next;
};

struct FList {
    int size;
    FNode* head;
};

void CreateFList(FList* flist);
FNode* CreateFNode(string data);
void FPushHead(FList* flist, string data);
void FPushBack(FList* flist, string data);
void FPushBefore(FList* flist, string data, string element);
void FPushAfter(FList* flist, string data, string element);
void FPopHead(FList* flist);
void FPopTail(FList* flist);
void FPopElement(FList* flist, string element);
bool FSearch(FList* flist, string element);
void PrintFList(FList* flist);
void DestroyFList(FList* flist);

#endif