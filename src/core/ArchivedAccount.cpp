#include "ArchivedAccount.h"
#include <iostream>
using namespace std;

ArchivedAccountArray createArchivedAccountArray(int initialCap = 5) {
    ArchivedAccountArray arr;
    arr.size = 0;
    arr.capacity = initialCap;
    arr.data = new ArchivedAccount[arr.capacity];
    return arr;
}

bool resizeArchivedArray(ArchivedAccountArray& arr) {
    int newCap = arr.capacity * 2;
    ArchivedAccount* newData = new (nothrow) ArchivedAccount[newCap];
    if (!newData) return false;

    for (int i = 0; i < arr.size; i++)
        newData[i] = arr.data[i];

    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCap;
    return true;
}

void addArchivedAccount(ArchivedAccountArray& arr, const Account& acc) {
    if (arr.size == arr.capacity) {
        resizeArchivedArray(arr);
    }
    arr.data[arr.size].acc = acc;
    arr.size++;
}
