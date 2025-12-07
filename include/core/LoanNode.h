#pragma once
#ifndef LOANNODE_H
#define	LOANNODE_H

#include "core/Loan.h"
using namespace std;

struct LoanNode {
    Loan data;
	LoanNode* next;
	LoanNode* prev;
};

struct LoanList {
    LoanNode* head;
    LoanNode* tail;
    int size;
};

#endif	//LOANNODE_H

