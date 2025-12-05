#pragma once
#ifndef ARCHIVEDACCOUNT_H
#define ARCHIVEDACCOUNT_H
#include "Account.h"
using namespace std;

struct ArchivedAccount {
    Account acc;
};

struct ArchivedAccountArray {
    ArchivedAccount* data;
    int size;
    int capacity;
};

ArchivedAccountArray createArchivedAccountArray(int initialCap = 5);
bool resizeArchivedArray(ArchivedAccountArray& arr);
void addArchivedAccount(ArchivedAccountArray& arr, const Account& acc);


#endif