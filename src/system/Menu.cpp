// src/system/Menu.cpp
#include <iostream>
#include <string>
#include "include/system/Menu.h"

using namespace std;

/* ---------------------------
   extern declarations
   adjust names if your .cpp uses different function names
   --------------------------- */

// Customer functions (implementations must exist elsewhere)
extern void DepositMoney(CustomerList& customers);
extern void WithdrawMoney(CustomerList& customers);
extern void SubmitLoanRequest(CustomerList& customers, LoanRequestQueue* queue);
extern void DisplayLoansByCustomer(CustomerList& customers);
extern void UndoLastTransaction(CustomerList& customers);
extern void DisplayTodayTransactions(CustomerList& customers);

// Employee functions
extern void AddEmployee(EmployeeArray& employees);
extern void RemoveEmployee(EmployeeArray& employees);
extern void ModifyEmployee(EmployeeArray& employees);
extern void AddCustomerAccount(CustomerList& customers);
extern void DisplayAllAccounts(CustomerList& customers);
extern void ChangeAccountStatus(CustomerList& customers);
extern void DeleteClosedAccounts(CustomerList& customers);
extern void DisplayLoansForCustomer(CustomerList& customers); // if different name, adapt
extern void ChangeLoanStatus(CustomerList& customers);
extern void DeleteCompletedLoans(CustomerList& customers, CompletedLoanList*& completedList);
extern void ManageLoanRequests(CustomerList& customers, LoanRequestQueue* queue);
extern void DisplayEmployeesAlphabetically(EmployeeArray& employees);
extern void DisplayEmployeesByBranch(const EmployeeArray& employees);

// Statistics functions (must exist)
extern int TotalNumberOfLoans(const CustomerList& customers);
extern int CountLoansByType(const CustomerList& customers, const string& type);
extern int CountLoansByStatus(const CustomerList& customers, const string& status);
extern int ActiveLoansInRange(const CustomerList& customers, const date& start, const date& end);
extern Customer* CustomerWithMostLoans(CustomerList& customers);
extern Customer* CustomerWithHighestBalance(CustomerList& customers);
extern Customer* CustomerWithLowestBalance(CustomerList& customers);
extern int TotalEmployees(const EmployeeArray& employees);
extern int EmployeesPerBranch(const EmployeeArray& employees, unsigned int branchCode);

// Finalize day wrapper
extern void FinalizeDay(CustomerList& customers, DailyLog* dailyLog);

/* ---------------------------
   Customer Menu
   --------------------------- */
void CustomerMenu(CustomerList& customers, LoanRequestQueue* queue) {
    int choice;
    while (true) {
        cout << "\n========== CUSTOMER INTERFACE ==========\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Submit Loan Request\n";
        cout << "4. Display My Loans\n";
        cout << "5. Undo Last Transaction\n";
        cout << "6. Display Today's Transactions\n";
        cout << "0. Back\n";
        cout << "=======================================\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000,'\n'); cout << "Invalid input.\n"; continue; }

        switch (choice) {
            case 1: DepositMoney(customers); break;
            case 2: WithdrawMoney(customers); break;
            case 3: SubmitLoanRequest(customers, queue); break;
            case 4: DisplayLoansByCustomer(customers); break;
            case 5: UndoLastTransaction(customers); break;
            case 6: DisplayTodayTransactions(customers); break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}

/* ---------------------------
   Statistics Menu - accessible ONLY via EmployeeMenu
   --------------------------- */
void StatisticsMenu(const CustomerList& customers, const EmployeeArray& employees) {
    int choice;
    while (true) {
        cout << "\n============= STATISTICS MENU =============\n";
        cout << "1. Total number of loans\n";
        cout << "2. Loans by type\n";
        cout << "3. Loans by status\n";
        cout << "4. Active loans in date range\n";
        cout << "5. Customer with most loans\n";
        cout << "6. Richest customer\n";
        cout << "7. Poorest customer\n";
        cout << "8. Total employees\n";
        cout << "9. Employees per branch\n";
        cout << "0. Back\n";
        cout << "===========================================\n";

        cout << "Enter choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000,'\n'); cout << "Invalid input.\n"; continue; }

        switch (choice) {
            case 1:
                cout << "Total loans: " << TotalNumberOfLoans(customers) << "\n";
                break;
            case 2: {
                string t; cout << "Enter loan type (car/home/student/business): "; cin >> t;
                cout << "Loans of type " << t << ": " << CountLoansByType(customers, t) << "\n";
                break;
            }
            case 3: {
                string s; cout << "Enter status (active/completed/overdue): "; cin >> s;
                cout << "Loans with status " << s << ": " << CountLoansByStatus(customers, s) << "\n";
                break;
            }
            case 4: {
                date start, end;
                cout << "Enter start date (day month year): "; cin >> start.day >> start.month >> start.year;
                cout << "Enter end date   (day month year): "; cin >> end.day >> end.month >> end.year;
                cout << "Active loans in range: " << ActiveLoansInRange(customers, start, end) << "\n";
                break;
            }
            case 5: {
                Customer* c = CustomerWithMostLoans(const_cast<CustomerList&>(customers));
                if (c) cout << "Customer: " << c->loginUsername << " | Account: " << c->account.Account_number << "\n";
                else cout << "No customers.\n";
                break;
            }
            case 6: {
                Customer* c = CustomerWithHighestBalance(const_cast<CustomerList&>(customers));
                if (c) cout << "Customer: " << c->loginUsername << " | Balance: " << c->account.Balance << "\n";
                else cout << "No customers.\n";
                break;
            }
            case 7: {
                Customer* c = CustomerWithLowestBalance(const_cast<CustomerList&>(customers));
                if (c) cout << "Customer: " << c->loginUsername << " | Balance: " << c->account.Balance << "\n";
                else cout << "No customers.\n";
                break;
            }
            case 8:
                cout << "Total employees: " << TotalEmployees(employees) << "\n";
                break;
            case 9: {
                unsigned int code; cout << "Enter branch code: "; cin >> code;
                cout << "Employees in branch " << code << ": " << EmployeesPerBranch(employees, code) << "\n";
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

/* ---------------------------
   Employee Menu (statistics is available here)
   --------------------------- */
void EmployeeMenu(CustomerList& customers, EmployeeArray& employees, LoanRequestQueue* queue, DailyLog* dailyLog) {
    int choice;
    while (true) {
        cout << "\n========== EMPLOYEE INTERFACE ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Modify Employee\n";
        cout << "4. Add Customer Account\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Change Account Status\n";
        cout << "7. Delete Closed Accounts\n";
        cout << "8. Display Loans for a Customer\n";
        cout << "9. Change Loan Status\n";
        cout << "10. Delete Completed Loans\n";
        cout << "11. Manage Loan Requests (FIFO)\n";
        cout << "12. Display Employees Alphabetically\n";
        cout << "13. Display Employees by Branch\n";
        cout << "14. Statistics Menu\n";
        cout << "15. Finalize Day\n";
        cout << "0. Back\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000,'\n'); cout << "Invalid input.\n"; continue; }

        switch (choice) {
            case 1: AddEmployee(employees); break;
            case 2: RemoveEmployee(employees); break;
            case 3: ModifyEmployee(employees); break;
            case 4: AddCustomerAccount(customers); break;
            case 5: DisplayAllAccounts(customers); break;
            case 6: ChangeAccountStatus(customers); break;
            case 7: DeleteClosedAccounts(customers); break;
            case 8: DisplayLoansForCustomer(customers); break;
            case 9: ChangeLoanStatus(customers); break;
            case 10: {
                CompletedLoanList* completed = nullptr;
                DeleteCompletedLoans(customers, completed);
                break;
            }
            case 11: ManageLoanRequests(customers, queue); break;
            case 12: DisplayEmployeesAlphabetically(employees); break;
            case 13: DisplayEmployeesByBranch(employees); break;
            case 14: StatisticsMenu(customers, employees); break;
            case 15: FinalizeDay(customers, dailyLog); break;
            case 0: return;
            default: cout << "Invalid option.\n"; break;
        }
    }
}
