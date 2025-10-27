#include "flist.h"
#include <iostream>

void CreateFList(FList* flist) {
    flist -> size = 0;
    flist -> head = nullptr;
}

FNode* CreateFNode(string data) {
    FNode* newNode = new FNode;
    newNode -> data = data;
    newNode -> next = nullptr;
    return newNode;
}

void FPushHead(FList* flist, string data) {
    FNode* newNode = CreateFNode(data);
    newNode -> next = flist -> head;
    flist -> head = newNode;
    flist -> size++;
}

void FPushBack(FList* flist, string data) {
    FNode* newNode = CreateFNode(data);
    if (flist -> head == nullptr) {
        flist -> head = newNode;
    } else {
        FNode* current = flist -> head;
        while (current -> next) current = current -> next;
        current -> next = newNode;
    }
    flist -> size++;
}

void FPushBefore(FList* flist, string data, string element) {
    if (flist -> head -> data == element) {
        FPushHead(flist, data);
        return;
    }
    FNode* current = flist -> head;
    while (current -> next && current -> next -> data != element) {
        current = current -> next;
    }
    if (current -> next) {
        FNode* newNode = CreateFNode(data);
        newNode -> next = current -> next;
        current -> next = newNode;
        flist -> size++;
    }
}

void FPushAfter(FList* flist, string data, string element) {
    FNode* current = flist -> head;
    while (current) {
        if (current -> data == element) {
            FNode* newNode = CreateFNode(data);
            newNode -> next = current -> next;
            current -> next = newNode;
            flist -> size++;
            return;
        }
        current = current -> next;
    }
}

void FPopHead(FList* flist) {
    if (!flist -> head) return;
    FNode* temp = flist -> head;
    flist -> head = flist -> head -> next;
    delete temp;
    flist -> size--;
}

void FPopTail(FList* flist) {
    if (!flist -> head) return;
    if (!flist -> head -> next) {
        delete flist -> head;
        flist -> head = nullptr;
        flist -> size--;
        return;
    }
    FNode* current = flist -> head;
    while (current -> next -> next) current = current -> next;
    delete current -> next;
    current -> next = nullptr;
    flist -> size--;
}

void FPopElement(FList* flist, string element) {
    if (!flist -> head) return;
    if (flist -> head -> data == element) {
        FPopHead(flist);
        return;
    }
    FNode* current = flist -> head;
    while (current -> next && current -> next -> data != element) {
        current = current -> next;
    }
    if (current -> next) {
        FNode* temp = current -> next;
        current -> next = current -> next -> next;
        delete temp;
        flist -> size--;
    }
}

bool FSearch(FList* flist, string element) {
    FNode* current = flist -> head;
    while (current) {
        if (current -> data == element) return true;
        current = current -> next;
    }
    return false;
}

void PrintFList(FList* flist) {
    cout << "[";
    FNode* current = flist -> head;
    while (current) {
        cout << current -> data;
        if (current -> next) cout << ", ";
        current = current -> next;
    }
    cout << "]" << endl;
}

void DestroyFList(FList* flist) {
    FNode* current = flist -> head;
    while (current) {
        FNode* temp = current;
        current = current -> next;
        delete temp;
    }
    flist -> head = nullptr;
}