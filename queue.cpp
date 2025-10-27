#include "queue.h"
#include <iostream>

void CreateQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->size = 0;
}

void QPush(Queue* queue, string data) {
    QNode* newNode = new QNode();
    newNode->data = data;
    newNode->next = nullptr;

    if (queue->tail != nullptr) {
        queue->tail->next = newNode;  // старый хвост указывает на новый узел
    } else {
        queue->head = newNode;  // если очередь пустая
    }

    queue->tail = newNode;  // новый узел становится хвостом
    queue->size++;
}

string QPop(Queue* queue) {
    if (queue->size == 0) return "";

    QNode* node = queue->head;
    string element = node->data;

    queue->head = node->next;  // сдвигаем голову

    if (queue->head == nullptr) {
        queue->tail = nullptr;  // если очередь опустела
    }

    delete node;
    queue->size--;
    return element;
}

void PrintQueue(Queue* queue) {
    cout << "[";
    QNode* current = queue->head;
    for (int i = 0; i < queue->size; i++) {
        cout << current->data;
        if (i < queue->size - 1) cout << ", ";
        current = current->next;
    }
    cout << "]" << endl;
}

void DestroyQueue(Queue* queue) {
    while (queue->head != nullptr) {
        QNode* temp = queue->head;
        queue->head = queue->head->next;
        delete temp;
    }
    queue->tail = nullptr;
    queue->size = 0;
}