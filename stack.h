#ifndef STACK_H
#define STACK_H
#include <string>
using namespace std;

struct Stack {
    int top;
    int capacity;
    string* data;
};

void CreateStack(Stack* stack, int capacity = 10);
void ResizeStack(Stack* stack);
void SPush(Stack* stack, string data);
string SPop(Stack* stack);
void PrintStack(Stack* stack);
void DestroyStack(Stack* stack);

#endif