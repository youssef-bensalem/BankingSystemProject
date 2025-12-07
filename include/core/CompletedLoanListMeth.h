#pragma once
#ifndef COMPLETEDLOANLISTMETH_H
#define	COMPLETEDLOANLISTMETH_H
#include "core/Loan.h"
#include "core/LoanNode.h"
#include "core/CompletedLoanNode.h"
using namespace std;

CompletedLoanList* createCompletedLoanList();
void destroyCompletedLoanList(CompletedLoanList& list);
CompletedLoanNode* createCompletedLoan(const Loan& loan);
void destroyCompletedLoan(CompletedLoanNode& completed_loan_node);
int findCompletedLoan(const Loan& loan, const CompletedLoanList& list);
int addCompletedLoan(CompletedLoanList& list, const Loan& loan);
int removeCompletedLoan(CompletedLoanList& list, unsigned int loanID);
int countCompletedLoans(const CompletedLoanList& list);
void printCompletedLoan(const CompletedLoanNode& loannode);
void printAllCompletedLoans(const CompletedLoanList& list);
bool isCompletedLoanListEmpty(CompletedLoanList& list);
bool isCompletedLoanListFull(CompletedLoanList& list);
void DisplayCompletedLoansByAccount(CompletedLoanList& list, const string& accountID);

#endif	//COMPLETEDLOANLISTMETH_H

