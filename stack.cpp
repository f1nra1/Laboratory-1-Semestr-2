#include "stack.h"
#include <iostream>

void CreateStack(Stack* stack) {
    stack -> top = nullptr;
    stack -> size = 0;
}

void SPush(Stack* stack, string data) {
    SNode* newNode = new SNode();
    newNode -> data = data;
    newNode -> next = stack -> top;
    stack -> top = newNode;
    stack -> size++;
}

string SPop(Stack* stack) {
    if (stack -> top == nullptr) {
        return "";
    }
    SNode* temp = stack -> top;
    string data = temp -> data;
    stack -> top = stack -> top -> next;
    stack -> size--;
    delete temp;
    return data;
}

void PrintStack(Stack* stack) {
    cout << "[";
    SNode* current = stack -> top;
    bool first = true;
    while (current != nullptr) {
        if (!first) cout << ", ";
        cout << current -> data;
        current = current -> next;
        first = false;
    }
    cout << "]" << endl;
}

void DestroyStack(Stack* stack) {
    while (stack -> top != nullptr) {
        SPop(stack);
    }
}