#ifndef EMPLOYEEUTILS_H
#define EMPLOYEEUTILS_H
#include <string>
#include "../core/Employee.h"
using namespace std;
bool resizeEmployeeArray(EmployeeArray& employees);
EmployeeArray createEmployeeArray(int initialCapacity);
void addEmployee(EmployeeArray& employees, const Employee& e);
int deleteEmployee(EmployeeArray& employees, unsigned int id);
int modifyEmployee(EmployeeArray& employees, unsigned int id);
void displayEmployeesAlphabetically(const EmployeeArray& employees);
void displayEmployeesByBranch(const EmployeeArray& employees);
void DisplayEarliestHiredEmployees(const EmployeeArray& employees);
void DisplayMostRecentlyHiredEmployee(const EmployeeArray& employees);
int AddCustomerAccount(CustomerList& list);
void DisplayAllAccounts(const CustomerList& list);
void ChangeAccountStatus(CustomerList& list, int account_number);
void DeleteClosedAccounts(CustomerList& customers, ArchivedAccountArray& archived);
void ManageLoanRequests(CustomerList& customers, LoanRequestQueue* queue);


#endif // EMPLOYEEUTILS_H