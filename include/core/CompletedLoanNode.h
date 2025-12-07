#pragma once
#ifndef COMPLETEDLOANNODE_H
#define COMPLETEDLOANNODE_H

#include "core/Loan.h"

struct CompletedLoanNode {
    Loan data;
    CompletedLoanNode* next;
};

struct CompletedLoanList {
    CompletedLoanNode* head;
    CompletedLoanNode* tail;
    int size;
};

#endif

