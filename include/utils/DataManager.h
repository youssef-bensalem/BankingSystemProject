#pragma once
#include "core/Customer.h"
#include "core/Employee.h"
#include "core/Account.h"
#include "utils/CustomerUtils.h"
#include "core/ArchivedAccount.h"
#include "core/CompletedLoanNode.h"
#include <string>

void LoadAll(CustomerList*& customers, EmployeeArray& employees, ArchivedAccountArray& archived, CompletedLoanList*& completedList);
void SaveAll(CustomerList* customers, const EmployeeArray& employees, const ArchivedAccountArray& archived, const CompletedLoanList* completedList);
