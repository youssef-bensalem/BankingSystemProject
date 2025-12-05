#ifndef CUSTOMERUTILS_H
#define CUSTOMERUTILS_H
#include "customer.h"
#include "LoanRequest.h"
#include "LoanListMeth.h"
#include <string>
using namespace std;

void createCustomerList(CustomerList& list);//done
int CustomerLogin(Customer* customer);//done
void DisplayLoansByCustomer(Customer* customer);//done
int SubmitLoanRequest(Customer* customer, LoanRequestQueue* queue);//done
int WithdrawMoney(Account* account);//done
int DepositMoney(Account* account);//done
void DisplayTodayTransactions(Account* account);//done
int UndoLastTransaction(Account* account) { //done

#endif // CUSTOMERUTILS_H