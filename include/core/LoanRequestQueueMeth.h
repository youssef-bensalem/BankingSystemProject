#pragma once
#ifndef LOANREQUESTQUEUEMETH_H
#define LOANREQUESTQUEUEMETH_H

#include "LoanRequest.h"
using namespace std;

LoanRequestQueue* createLoanRequestQueue();
void destroyLoanRequestQueue(LoanRequestQueue* queue);

LoanRequestNode* createLoanRequestNode(const LoanRequest& request);
int enqueueLoanRequest(LoanRequestQueue* queue, const LoanRequest& request);
LoanRequest dequeueLoanRequest(LoanRequestQueue* queue);

bool LoanRequestQueueEmpty(const LoanRequestQueue& queue);
bool LoanRequestQueueFull(const LoanRequestQueue& queue);

int getLoanRequestQueueSize(const LoanRequestQueue& queue);
void printLoanRequest(const LoanRequest& request);
void printAllLoanRequests(const LoanRequestQueue& queue);

#endif 
