#pragma once
#ifndef ARCHIVEDACCOUNT_H
#define ARCHIVEDACCOUNT_H
#include "core/Account.h"
using namespace std;

struct ArchivedAccount {
    Account* acc;
};

struct ArchivedAccountArray {
    ArchivedAccount* data;
    int size;
    int capacity;
};

ArchivedAccountArray createArchivedAccountArray(int initialCap);
bool resizeArchivedArray(ArchivedAccountArray& arr);
void addArchivedAccount(ArchivedAccountArray& arr, Account* acc);

#endif