#include "queue.h"
#include <iostream>

void CreateQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->size = 0;
}

void QPush(Queue* queue, string data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = queue->tail;

    if (queue->tail != nullptr) {
        queue->tail->next = newNode;
    } else {
        queue->head = newNode;
    }

    queue->tail = newNode;
    queue->size++;
}

string QPop(Queue* queue) {
    if (queue->size == 0) return "";

    Node* node = queue->head;
    string element = node->data;

    queue->head = node->next;
    if (queue->head != nullptr) {
        queue->head->prev = nullptr;
    } else {
        queue->tail = nullptr;
    }

    delete node;
    queue->size--;
    return element;
}

void PrintQueue(Queue* queue) {
    cout << "[";
    Node* current = queue->head;
    for (int i = 0; i < queue->size; i++) {
        cout << current->data;
        if (i < queue->size - 1) cout << ", ";
        current = current->next;
    }
    cout << "]" << endl;
}

void DestroyQueue(Queue* queue) {
    while (queue->head != nullptr) {
        Node* temp = queue->head;
        queue->head = queue->head->next;
        delete temp;
    }
    queue->tail = nullptr;
    queue->size = 0;
}