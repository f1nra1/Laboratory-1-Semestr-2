#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include <string>
#include "array.h"
#include "flist.h"
#include "llist.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"

using namespace std;

struct Database {
    map<string, MArray*> arrays;
    map<string, FList*> flists;
    map<string, LList*> llists;
    map<string, Stack*> stacks;
    map<string, Queue*> queues;
    map<string, BinaryTree*> trees;
};

extern Database db;
extern string dataFile;

void SaveDatabase();
void LoadDatabase();
void ExecuteQuery(string query);
void CleanupDatabase();

#endif