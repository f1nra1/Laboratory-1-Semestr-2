#include "llist.h"
#include <iostream>

void CreateLList(LList* llist) {
    llist -> size = 0;
    llist -> head = nullptr;
    llist -> tail = nullptr;
}

LNode* CreateLNode(string data) {
    LNode* newNode = new LNode;
    newNode -> data = data;
    newNode -> pNext = nullptr;
    newNode -> pPrev = nullptr;
    return newNode;
}

void LPushHead(LList* llist, string data) {
    LNode* newNode = CreateLNode(data);
    if (!llist -> head) {
        llist -> head = llist -> tail = newNode;
    } else {
        newNode -> pNext = llist -> head;
        llist -> head -> pPrev = newNode;
        llist -> head = newNode;
    }
    llist -> size++;
}

void LPushTail(LList* llist, string data) {
    LNode* newNode = CreateLNode(data);
    if (!llist -> head) {
        llist -> head = llist -> tail = newNode;
    } else {
        newNode -> pPrev = llist -> tail;
        llist -> tail -> pNext = newNode;
        llist -> tail = newNode;
    }
    llist -> size++;
}

void LPushBefore(LList* llist, string data, string element) {
    if (llist -> head -> data == element) {
        LPushHead(llist, data);
        return;
    }
    LNode* current = llist -> head;
    while (current && current -> data != element) {
        current = current -> pNext;
    }
    if (current) {
        LNode* newNode = CreateLNode(data);
        newNode -> pNext = current;
        newNode -> pPrev = current -> pPrev;
        if (current -> pPrev) current -> pPrev -> pNext = newNode;
        current -> pPrev = newNode;
        llist -> size++;
    }
}

void LPushAfter(LList* llist, string data, string element) {
    if (!llist -> head) return;
    if (llist -> tail -> data == element) {
        LPushTail(llist, data);
        return;
    }
    LNode* current = llist -> head;
    while (current && current -> data != element) {
        current = current -> pNext;
    }
    if (current) {
        LNode* newNode = CreateLNode(data);
        newNode -> pPrev = current;
        newNode -> pNext = current -> pNext;
        if (current -> pNext) current -> pNext -> pPrev = newNode;
        current -> pNext = newNode;
        llist -> size++;
    }
}

void LPopHead(LList* llist) {
    if (!llist -> head) return;
    LNode* temp = llist -> head;
    llist -> head = llist -> head -> pNext;
    if (llist -> head) llist -> head -> pPrev = nullptr;
    else llist -> tail = nullptr;
    delete temp;
    llist -> size--;
}

void LPopTail(LList* llist) {
    if (!llist -> head) return;
    if (!llist -> tail -> pPrev) {
        delete llist -> head;
        llist -> head = llist -> tail = nullptr;
        llist -> size--;
        return;
    }
    LNode* temp = llist -> tail;
    llist -> tail = llist -> tail -> pPrev;
    llist -> tail -> pNext = nullptr;
    delete temp;
    llist -> size--;
}

void LPopElement(LList* llist, string element) {
    if (!llist -> head) return;
    LNode* current = llist -> head;
    while (current && current -> data != element) {
        current = current -> pNext;
    }
    if (current) {
        if (!current -> pPrev) LPopHead(llist);
        else if (!current -> pNext) LPopTail(llist);
        else {
            current -> pPrev -> pNext = current -> pNext;
            current -> pNext -> pPrev = current -> pPrev;
            delete current;
            llist -> size--;
        }
    }
}

bool LSearch(LList* llist, string element) {
    LNode* current = llist -> head;
    while (current) {
        if (current -> data == element) return true;
        current = current -> pNext;
    }
    return false;
}

void PrintLList(LList* llist) {
    cout << "[";
    LNode* current = llist -> head;
    while (current) {
        cout << current -> data;
        if (current -> pNext) cout << ", ";
        current = current -> pNext;
    }
    cout << "]" << endl;
}

void DestroyLList(LList* llist) {
    LNode* current = llist -> head;
    while (current) {
        LNode* temp = current;
        current = current -> pNext;
        delete temp;
    }
    llist -> head = llist -> tail = nullptr;
}