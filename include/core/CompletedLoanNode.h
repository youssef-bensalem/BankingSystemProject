#pragma once
#ifndef COMPLETEDLOANNODE_H
#define COMPLETEDLOANNODE_H

#include "Loan.h"

struct CompletedLoanNode {
    Loan data;
    CompletedLoanNode* next;
};

struct CompletedLoanList {
    CompletedLoanNode* head;
};

#endif

