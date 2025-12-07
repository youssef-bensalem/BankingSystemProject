#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "core/Account.h"
using namespace std;

struct Customer {
    string loginUsername;
    string loginPassword;
    Account* account;
};

struct CustomerNode {
    Customer* data;
    CustomerNode* next;
};

struct CustomerList {
    CustomerNode* head;
};

#endif