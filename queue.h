#ifndef QUEUE_H
#define QUEUE_H
#include <string>
using namespace std;

struct QNode {
    string data;
    QNode* next;
    QNode* prev;
};

struct Queue {
    QNode* head;
    QNode* tail;
    int size;
};

void CreateQueue(Queue* queue);
void QPush(Queue* queue, string data);
string QPop(Queue* queue);
void PrintQueue(Queue* queue);
void DestroyQueue(Queue* queue);

#endif