#ifndef CUSTOMERUTILS_H
#define CUSTOMERUTILS_H
#include "core/Customer.h"
#include "core/LoanRequest.h"
#include "core/TransactionStackMeth.h"
#include "core/LoanRequestQueueMeth.h"
#include "core/LoanListMeth.h"
#include <string>
#include <iostream>
using namespace std;

bool CustomerLogin(CustomerList* &customers, Customer* &loggedInCustomer);
void createCustomerList(CustomerList* &list);
int CustomerLogin(Customer* customer);
void DisplayLoansByCustomer(Customer* customer);
int SubmitLoanRequest(Customer* customer, LoanRequestQueue* queue);
int WithdrawMoney(Account* account);
int DepositMoney(Account* account);
void DisplayTodayTransactions(Account* account);
int UndoLastTransaction(Account* account) ;
#endif // CUSTOMERUTILS_H