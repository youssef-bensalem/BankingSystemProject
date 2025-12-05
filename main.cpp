#include "../core/Customer.h"
#include "../core/Employee.h"
#include "../core/LoanRequest.h"
#include "../core/Transaction.h"
#include "../system/Statistics.h"
#include "../utils/CustomerUtils.h"
#include "../utils/EmployeeUtils.h"
#include <iostream>

using namespace std;

#include <iostream>
using namespace std;

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
        cin >> choice;

        switch (choice) {

        case 1:
            DepositMoney(customers);
            break;

        case 2:
            WithdrawMoney(customers);
            break;

        case 3:
            SubmitLoanRequest(customers, queue);
            break;

        case 4:
            DisplayLoansByCustomer(customers);
            break;

        case 5:
            UndoLastTransaction(customers);
            break;

        case 6:
            DisplayTodayTransactions(customers);
            break;

        case 0:
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

void EmployeeMenu(CustomerList& customers, EmployeeArray& employees, LoanRequestQueue* queue) {
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
        cout << "0. Back\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: AddEmployee(employees); break;
        case 2: RemoveEmployee(employees); break;
        case 3: ModifyEmployee(employees); break;
        case 4: AddCustomerAccount(customers); break;
        case 5: DisplayAllAccounts(customers); break;
        case 6: ChangeAccountStatus(customers); break;
        case 7: DeleteClosedAccounts(customers); break;
        case 8: DisplayLoansByCustomer(customers); break;
        case 9: ChangeLoanStatus(customers); break;
        case 10: DeleteCompletedLoans(customers); break;
        case 11: ManageLoanRequests(customers, queue); break;
        case 12: DisplayEmployeesAlphabetically(employees); break;
        case 13: DisplayEmployeesByBranch(employees); break;
        case 0: return;
        default: cout << "Invalid option.\n"; break;
        }
    }
}

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
        cin >> choice;

        switch (choice) {
        case 1: cout << TotalNumberOfLoans(customers); break;
        case 2: /* ask type */ break;
        case 3: /* ask status */ break;
        case 4: /* ask date range */ break;
        case 5: CustomerWithMostLoans(customers); break;
        case 6: CustomerWithHighestBalance(customers); break;
        case 7: CustomerWithLowestBalance(customers); break;
        case 8: cout << TotalEmployees(employees); break;
        case 9: /* ask branch */ break;
        case 0: return;
        default: cout << "Invalid choice.\n"; break;
        }
    }
}



CustomerList customers;
EmployeeArray employees;
LoanRequestQueue* requestQueue;

int main() {

    // Initialize main structures
    customers.head = nullptr;

    employees.data = nullptr;
    employees.size = 0;
    employees.capacity = 0;

    requestQueue = createLoanRequestQueue();

    int choice;

    while (true) {

        cout << "\n";
        cout << " -------------------------------------------------------------------\n";
        cout << "|                   Welcome to the Banking Management System        |\n";
        cout << " -------------------------------------------------------------------\n";
        cout << "|                                                                   |\n";
        cout << "|                     1 - Customer interface                        |\n";
        cout << "|                     2 - Employee interface                        |\n";
        cout << "|                                                                   |\n";
        cout << "|                     3 - Exit                                      |\n";
        cout << "|                                                                   |\n";
        cout << " -------------------------------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CustomerMenu(customers, requestQueue);
            break;

        case 2:
            EmployeeMenu(customers, employees, requestQueue);
            break;

        case 3:
            cout << "\nExiting system...\n";
            return 0;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}
