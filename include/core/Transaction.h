#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;
#include "utils/Date.h"

struct Transaction {
    unsigned int Transaction_ID;
    unsigned int Account_Number;
    string Type;       // deposit or withdrawal
    double Amount;
    date Date; 
};
struct StackNode {
    Transaction transaction;
    StackNode* next;
};

struct TransactionStack {
    StackNode* top;
};  

#endif


