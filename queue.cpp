#include "queue.h"
#include <iostream>

void CreateQueue(Queue* queue, int capacity) {
    queue -> data = new string[capacity];
    queue -> head = 0;
    queue -> tail = -1;
    queue -> capacity = capacity;
    queue -> size = 0;
}

void ResizeQueue(Queue* queue) {
    int newCapacity = queue -> capacity * 2;
    string* newData = new string[newCapacity];
    for (int i = 0; i < queue -> size; i++) {
        newData[i] = queue -> data[(queue -> head + i) % queue -> capacity];
    }
    delete[] queue -> data;
    queue -> data = newData;
    queue -> head = 0;
    queue -> tail = queue -> size - 1;
    queue -> capacity = newCapacity;
}

void QPush(Queue* queue, string data) {
    if (queue -> size >= queue -> capacity) ResizeQueue(queue);
    queue -> tail = (queue -> tail + 1) % queue -> capacity;
    queue -> data[queue -> tail] = data;
    queue -> size++;
}

string QPop(Queue* queue) {
    if (queue -> size == 0) return "";
    string element = queue -> data[queue -> head];
    queue -> head = (queue -> head + 1) % queue -> capacity;
    queue -> size--;
    return element;
}

void PrintQueue(Queue* queue) {
    cout << "[";
    for (int i = 0; i < queue -> size; i++) {
        cout << queue -> data[(queue -> head + i) % queue -> capacity];
        if (i < queue -> size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void DestroyQueue(Queue* queue) {
    if (queue) delete[] queue -> data;
}