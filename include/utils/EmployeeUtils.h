#ifndef EMPLOYEEUTILS_H
#define EMPLOYEEUTILS_H
#include "core/Employee.h"
#include "core/customer.h"
#include "core/Account.h"
#include "core/Transaction.h"
#include "core/TransactionStackMeth.h"
#include "core/LoanRequest.h"
#include "core/LoanNode.h"
#include "core/LoanListMeth.h"
#include "core/ArchivedAccount.h"
#include "core/CompletedLoanListMeth.h"
#include "core/LoanRequestQueueMeth.h"
#include "utils/EmployeeUtils.h"
#include <string>
#include <iostream>
using namespace std;

bool IsAlphabetic(const string &str);
bool resizeEmployeeArray(EmployeeArray& employees);
EmployeeArray createEmployeeArray(int initialCapacity);
void addEmployee(EmployeeArray& employees, const Employee& e);
int deleteEmployee(EmployeeArray& employees, unsigned int id);
int modifyEmployee(EmployeeArray& employees, unsigned int id);
void displayEmployeesAlphabetically(const EmployeeArray& employees);
bool existInArray(const int arr[], int e);
void displayEmployeesByBranch(const EmployeeArray& employees);
void DisplayEarliestHiredEmployees(const EmployeeArray& employees);
void DisplayMostRecentlyHiredEmployee(const EmployeeArray& employees);
int AddCustomerAccount(CustomerList* &list);
void DisplayAllAccounts(CustomerList* &list);
void ChangeAccountStatus(CustomerList* list, unsigned int account_number);
void DeleteClosedAccounts(CustomerList* customers, ArchivedAccountArray& archived);
void ChangeLoanStatus(CustomerList* customers);
void DeleteCompletedLoans(CustomerList* customers, CompletedLoanList*& completedList);
CustomerNode* findCustomerAccount(CustomerList*customers, unsigned int accountNumber);
int AddLoanToCustomer(Customer* customer, const Loan& loan);
void DeclineLoanRequest(const LoanRequest& request);
void AcceptLoanRequest(CustomerList* customers, const LoanRequest& request);
void ManageLoanRequests(CustomerList* customers, LoanRequestQueue* queue);


void finalizeAllAccounts(CustomerList* customers);

void DisplayDayHistory(Account* acc);
#endif // EMPLOYEEUTILS_H