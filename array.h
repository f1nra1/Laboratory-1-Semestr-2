#ifndef ARRAY_H
#define ARRAY_H
#include <string>
using namespace std;

struct MArray {
    string* data;
    int size;
    int capacity;
};

void CreateMArray(MArray* arr, int capacity = 10);
void ResizeMArray(MArray* arr);
void MPushBack(MArray* arr, string element);
void MPushIndex(MArray* arr, string element, int index);
string MGet(MArray* arr, int index);
void MPopIndex(MArray* arr, int index);
void MReplace(MArray* arr, string element, int index);
int MGetSize(MArray* arr);
void PrintMArray(MArray* arr);
void DestroyMArray(MArray* arr);

#endif
