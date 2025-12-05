#pragma once
#ifndef LOANLISTMETH_H
#define LOANLISTMETH_H

#include "LoanNode.h"
#include <string>
using namespace std;

LoanList createLoanList();
void destroyLoanList(LoanList& list);
LoanNode* createLoanNode(const Loan& loan);
int insertLoan(LoanList& list, const Loan& loan);
int removeLoan(LoanList& list, const string& ID);
LoanNode* findLoan(LoanNode* head, unsigned int loanID);
int countLoans(const LoanList& list);
void printLoan(const Loan& loan);
void printAllLoans(const LoanList& list);
bool LoanListEmpty(LoanList& list);
bool LoanListFull(LoanList& list);
int updateLoanPayment(LoanList& list, const string& loanID, double paymentAmount);


#endif // LOANLISTMETH_H





