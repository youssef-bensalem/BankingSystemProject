#pragma once
#ifndef LOANLISTMETH_H
#define LOANLISTMETH_H

#include "LoanNode.h"
#include <iostream>
using namespace std;

LoanNode* createLoanNode(const Loan& loan);
LoanList* createLoanList();
void destroyLoanList(LoanList* list);
int insertLoan(LoanList* list, const Loan& loan);
bool LoanListEmpty(const LoanList& list);
bool LoanListFull(LoanList& list);
int removeLoan(LoanList* list, unsigned int ID);
int countLoans(const LoanList& list);
LoanNode* findLoan(LoanNode* head, unsigned int loanID);
void printLoan(const Loan* loan);
void printAllLoans(const LoanList* list);
int updateLoanPayment(LoanList* list, unsigned int loanID, double paymentAmount);

#endif // LOANLISTMETH_H





