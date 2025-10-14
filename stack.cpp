#include "stack.h"
#include <iostream>

void CreateStack(Stack* stack, int capacity) {
    stack -> data = new string[capacity];
    stack -> top = -1;
    stack -> capacity = capacity;
}

void ResizeStack(Stack* stack) {
    int newCapacity = stack -> capacity * 2;
    string* newData = new string[newCapacity];
    for (int i = 0; i <= stack -> top; i++) {
        newData[i] = stack -> data[i];
    }
    delete[] stack -> data;
    stack -> data = newData;
    stack -> capacity = newCapacity;
}

void SPush(Stack* stack, string data) {
    if (stack -> top >= stack -> capacity - 1) ResizeStack(stack);
    stack -> data[++stack -> top] = data;
}

string SPop(Stack* stack) {
    if (stack -> top < 0) return "";
    return stack -> data[stack -> top--];
}

void PrintStack(Stack* stack) {
    cout << "[";
    for (int i = 0; i <= stack -> top; i++) {
        cout << stack -> data[i];
        if (i < stack -> top) cout << ", ";
    }
    cout << "]" << endl;
}

void DestroyStack(Stack* stack) {
    if (stack) delete[] stack -> data;
}