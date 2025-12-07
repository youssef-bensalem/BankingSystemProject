#pragma once
#ifndef LOANREQUEST_H
#define LOANREQUEST_H

#include <string>
using namespace std;
#include "utils/Date.h"

struct LoanRequest {
    unsigned int requestID;        // Unique request ID
    unsigned int accountNumber;
    string loanType;               // car, home, business, student
    double requestedAmount;
    double interestRate;           // Proposed interest rate
    unsigned int durationMonths;   // Duration of loan
    date requestDate;              // Date when request was made
    string status;                 // pending, accepted, declined 
};

struct LoanRequestNode {
    LoanRequest data;
    LoanRequestNode* next;
};

struct LoanRequestQueue {
    LoanRequestNode* front;
    LoanRequestNode* tail;
};

#endif // LOANREQUEST_H


