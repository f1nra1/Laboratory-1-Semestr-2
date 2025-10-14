#include "array.h"
#include <iostream>

void CreateMArray(MArray* arr, int capacity) {
    arr -> size = 0;
    arr -> capacity = capacity;
    arr -> data = new string[arr -> capacity];
}

void ResizeMArray(MArray* arr) {
    int newCapacity = arr -> capacity * 2;
    string* newData = new string[newCapacity];
    for (int i = 0; i < arr -> size; i++) {
        newData[i] = arr -> data[i];
    }
    delete[] arr -> data;
    arr -> data = newData;
    arr -> capacity = newCapacity;
}

void MPushBack(MArray* arr, string element) {
    if (arr -> size == arr -> capacity) ResizeMArray(arr);
    arr -> data[arr -> size] = element;
    arr -> size++;
}

void MPushIndex(MArray* arr, string element, int index) {
    if (index < 0 || index > arr -> size) return;
    if (arr -> size >= arr -> capacity) ResizeMArray(arr);
    for (int i = arr -> size; i > index; i--) {
        arr -> data[i] = arr -> data[i - 1];
    }
    arr -> data[index] = element;
    arr -> size++;
}

string MGet(MArray* arr, int index) {
    if (index < 0 || index >= arr -> size) return "";
    return arr -> data[index];
}

void MPopIndex(MArray* arr, int index) {
    if (arr -> size == 0 || index < 0 || index >= arr -> size) return;
    for (int i = index; i < arr -> size - 1; i++) {
        arr -> data[i] = arr -> data[i + 1];
    }
    arr -> size--;
}

void MReplace(MArray* arr, string element, int index) {
    if (index < 0 || index >= arr -> size) return;
    arr -> data[index] = element;
}

int MGetSize(MArray* arr) {
    return arr -> size;
}

void PrintMArray(MArray* arr) {
    cout << "[";
    for (int i = 0; i < arr -> size; i++) {
        cout << arr -> data[i];
        if (i < arr -> size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void DestroyMArray(MArray* arr) {
    if (arr) delete[] arr -> data;
}