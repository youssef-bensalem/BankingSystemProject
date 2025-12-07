#ifndef STATISTICS_H
#define STATISTICS_H

#include "core/LoanNode.h"
#include "core/Customer.h"
#include "core/Employee.h"
#include "utils/Date.h"

#include <iostream>

using namespace std;

int TotalNumberOfLoans(CustomerList* customers);
int CountLoansByType(CustomerList* customers, const string& type);
int CountLoansByStatus(CustomerList* customers, const string& status);
int compareDates(const date& a, const date& b);
int ActiveLoansInRange(CustomerList* customers, const date& startD, const date& endD);
Customer* CustomerWithMostLoans(CustomerList* customers);
Customer* CustomerWithHighestBalance(CustomerList* customers);
Customer* CustomerWithLowestBalance(CustomerList* customers);
int TotalEmployees(const EmployeeArray& employees);
int EmployeesPerBranch(const EmployeeArray& employees, unsigned int branchCode);

#endif
