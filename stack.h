#ifndef STACK_H
#define STACK_H
#include <string>
using namespace std;

struct SNode {
    string data;
    SNode* next;
};

struct Stack {
    SNode* top;
    int size;
};

void CreateStack(Stack* stack);
void SPush(Stack* stack, string data);
string SPop(Stack* stack);
void PrintStack(Stack* stack);
void DestroyStack(Stack* stack);

#endif