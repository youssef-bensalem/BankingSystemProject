// include/system/Menu.h
#pragma once
#ifndef MENU_H
#define MENU_H

#include "../core/Customer.h"
#include "../core/Employee.h"
#include "../core/LoanRequest.h"
#include "../core/Transaction.h"
#include "../utils/Date.h"
#include "../core/CompletedLoanList.h" // optional: adapt if different
#include "../system/DailyLog.h" // optional: adapt if you used DailyLog.h

// Customer menu: interacts with customers and loan request queue
void CustomerMenu(CustomerList& customers, LoanRequestQueue* queue);

// Employee menu: interacts with employees, customers, queue, daily log
void EmployeeMenu(CustomerList& customers, EmployeeArray& employees, LoanRequestQueue* queue, DailyLog* dailyLog);

// Statistics menu (called only from employee menu)
void StatisticsMenu(const CustomerList& customers, const EmployeeArray& employees);

// wrapper for finalizing the day (if you use a different name, change it)
void FinalizeDayWrapper(CustomerList& customers, DailyLog* dailyLog);

#endif // MENU_H

