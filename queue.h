#ifndef QUEUE_H
#define QUEUE_H
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
    Node* prev;
};

struct Queue {
    Node* head;
    Node* tail;
    int size;
};

void CreateQueue(Queue* queue);
void QPush(Queue* queue, string data);
string QPop(Queue* queue);
void PrintQueue(Queue* queue);
void DestroyQueue(Queue* queue);

#endif