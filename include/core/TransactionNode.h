#pragma once
#ifndef TRANSACTIONNODE_H
#define TRANSACTIONNODE_H

#include "core/Transaction.h"

struct TransactionNode {
    Transaction data;
    TransactionNode* next;
};

#endif
