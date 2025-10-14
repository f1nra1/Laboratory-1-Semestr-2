#ifndef QUEUE_H
#define QUEUE_H
#include <string>
using namespace std;

struct Queue {
    int head, tail, capacity, size;
    string* data;
};

void CreateQueue(Queue* queue, int capacity = 10);
void ResizeQueue(Queue* queue);
void QPush(Queue* queue, string data);
string QPop(Queue* queue);
void PrintQueue(Queue* queue);
void DestroyQueue(Queue* queue);

#endif