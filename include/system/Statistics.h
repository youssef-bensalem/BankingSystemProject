#ifndef STATISTICS_H
#define STATISTICS_H

#include "../core/LoanNode.h"
#include "../core/Customer.h"
#include "../core/EmployeeArray.h"
#include "../utils/Date.h"

int TotalNumberOfLoans(const CustomerList& customers);
int CountLoansByType(const CustomerList& customers, const string& type);
int CountLoansByStatus(const CustomerList& customers, const string& status);
int ActiveLoansInRange(const CustomerList& customers, const date& start, const date& end);

Customer* CustomerWithMostLoans(CustomerList& customers);
Customer* CustomerWithHighestBalance(CustomerList& customers);
Customer* CustomerWithLowestBalance(CustomerList& customers);

int TotalEmployees(const EmployeeArray& employees);
int EmployeesPerBranch(const EmployeeArray& employees, unsigned int branchCode);

#endif
