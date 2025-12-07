// =========================
// FIX 1: Forward declaration
// =========================
class CompletedLoanList;

#include "core/Customer.h"
#include "core/Employee.h"
#include "core/LoanRequest.h"
#include "core/Transaction.h"
#include "system/Statistics.h"
#include "utils/CustomerUtils.h"
#include "utils/EmployeeUtils.h"
#include "core/ArchivedAccount.h"
#include "core/CompletedLoanListMeth.h"
#include "core/LoanRequestQueueMeth.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

// =====================================
// CUSTOMER SEARCH / INSERT HELPERS
// =====================================

void AddCustomerNode(CustomerList &list, Customer* c)
{
    CustomerNode *node = new CustomerNode;
    node->data = c;
    node->next = list.head;
    list.head = node;
}

Customer *FindCustomerByAccountNumber(CustomerList* list, unsigned int accNum)
{
    CustomerNode *cur = list->head;
    while (cur)
    {
        if (cur->data->account->Account_number == accNum)
            return cur->data;
        cur = cur->next;
    }
    return nullptr;
}

// =====================================
// EMPLOYEE FILE-LOAD / SAVE HELPERS
// =====================================

void CustomerMenu(CustomerList* &customers, LoanRequestQueue *queue, Customer *loggedIn)
{
    cout << "\nLogged in as: " << loggedIn->loginUsername << endl;
    int choice;

    while (true)
    {
        cout << "\n==== CUSTOMER MENU ====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Submit loan request\n";
        cout << "4. Display loans\n";
        cout << "5. Undo last transaction\n";
        cout << "6. Today's transactions\n";
        cout << "0. Back\nChoice: ";
        cin >> choice;
        // BONUS FIX FOR INVALID NON-INT INPUT
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid input! Please enter a number: ";
            cin >> choice;
        }
        if (choice == 0)
            return;

        switch (choice)
        {
        case 1:
            DepositMoney(loggedIn->account);
            break;
        case 2:
            WithdrawMoney(loggedIn->account);
            break;
        case 3:
            SubmitLoanRequest(loggedIn, queue);
            break;
        case 4:
            DisplayLoansByCustomer(loggedIn);
            break;
        case 5:
            UndoLastTransaction(loggedIn->account);
            break;
        case 6:
            DisplayTodayTransactions(loggedIn->account);
            break;
        }
    }
}

// =====================================
// EMPLOYEE MENU
// =====================================

void EmployeeMenu(CustomerList* &customers,
                  EmployeeArray &employees,
                  LoanRequestQueue *queue,
                  ArchivedAccountArray &archived,
                  CompletedLoanList *&completedList)
{
    int choice;
    unsigned int id;

    while (true)
    {
        cout << "\n==== EMPLOYEE MENU ====\n";
        cout << "1. Add employee\n";
        cout << "2. Remove employee\n";
        cout << "3. Modify employee\n";
        cout << "4. Add customer account\n";
        cout << "5. Display all accounts\n";
        cout << "6. Change account status\n";
        cout << "7. Delete closed accounts\n";
        cout << "8. Display loans for a customer\n";
        cout << "9. Change loan status\n";
        cout << "10. Delete completed loans\n";
        cout << "11. Manage Loan Requests (FIFO)\n";
        cout << "12. Display Employees Alphabetically\n";
        cout << "13. Display Employees by Branch\n";
        cout << "0. Back\nChoice: ";

        cin >> choice;
        // BONUS FIX FOR INVALID NON-INT INPUT
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid input! Please enter a number: ";
            cin >> choice;
        }
        if (choice == 0)
            return;

        switch (choice)
        {
        case 1:
        {
            Employee e;

            cout << "ID: ";
            while (!(cin >> e.Id))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a valid ID: ";
            }

            // Clear leftover newline before getline
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

            cout << "Name: ";
            getline(cin, e.Name);

            cout << "Last name: ";
            getline(cin, e.Last_name);

            cout << "Address: ";
            getline(cin, e.Address);

            cout << "Salary: ";
            while (!(cin >> e.salary))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a valid salary: ";
            }

            cout << "Hire d m y: ";
            while (!(cin >> e.Hire_date.day >> e.Hire_date.month >> e.Hire_date.year))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a valid date (d m y): ";
            }

            cout << "Branch: ";
            while (!(cin >> e.Bank_branch))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a valid bank branch: ";
            }

            addEmployee(employees, e);
            break;
        }
        case 2:
            cout << "Employee Id: ";
            cin >> id;
            deleteEmployee(employees, id);
            break;

        case 3:
            cout << "Employee Id: ";
            cin >> id;
            modifyEmployee(employees, id);
            break;

        case 4:
        {
            int added = 0;
            while (!added) {
                added = AddCustomerAccount(customers);
            }
            break;
        }
        case 5:
            DisplayAllAccounts(customers);
            break;

        case 6:
            cout << "Account number: ";
            unsigned int accNum;
            cin >> accNum;
            ChangeAccountStatus(customers, accNum);
            break;

        case 7:
            DeleteClosedAccounts(customers, archived);
            break;

        case 8:
        {
            cout << "Account number: ";
            unsigned int accNum;
            cin >> accNum;
            Customer *c = FindCustomerByAccountNumber(customers, accNum);
            if (!c)
                cout << "Not found.\n";
            else
                DisplayLoansByCustomer(c);

            break;
        }
        case 9:
            ChangeLoanStatus(customers);
            break;

        case 10:
            DeleteCompletedLoans(customers, completedList);
            break;

        case 11:
            ManageLoanRequests(customers, queue);
            break;

        case 12:
            displayEmployeesAlphabetically(employees);
            break;

        case 13:
            displayEmployeesByBranch(employees);
            break;

        default:
            cout << "Invalid option.\n";
            break;
        }
    }
}

// =====================================
// STATISTICS MENU
// =====================================

void StatisticsMenu(CustomerList* customers, const EmployeeArray &employees)
{
    int choice;

    while (true)
    {
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
        // BONUS FIX FOR INVALID NON-INT INPUT
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid input! Please enter a number: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            cout << TotalNumberOfLoans(customers);
            break;
        case 2: /* ask type */
            break;
        case 3: /* ask status */
            break;
        case 4: /* ask date range */
            break;
        case 5:
            CustomerWithMostLoans(customers);
            break;
        case 6:
            CustomerWithHighestBalance(customers);
            break;
        case 7:
            CustomerWithLowestBalance(customers);
            break;
        case 8:
            cout << TotalEmployees(employees);
            break;
        case 9: /* ask branch */
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

// =====================================
// MAIN
// =====================================

int main()
{
    CustomerList* customers;
    createCustomerList(customers);

    EmployeeArray employees = createEmployeeArray(10);

    LoanRequestQueue *queue = createLoanRequestQueue();
    ArchivedAccountArray archived = createArchivedAccountArray(5);

    // FIX: Correct type expected by header
    CompletedLoanList *completedList = createCompletedLoanList();

    int choice;
    while (true)
    {
        cout << "\n==== MAIN MENU ====\n";
        cout << "1. Customer\n";
        cout << "2. Employee\n";
        cout << "3. Statistics\n";
        cout << "0. Exit\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Customer *loggedInCustomer = nullptr;
            int attempts = 3;
            while (attempts-- > 0 && !CustomerLogin(customers, loggedInCustomer))
            {
                cout << "Retrying login... (Attempts left: " << attempts << "/3):" << endl;
            }
            if (attempts < 0)
                continue;

            CustomerMenu(customers, queue, loggedInCustomer);

            break;
        }
        case 2:
            EmployeeMenu(customers, employees, queue, archived, completedList);
            break;

        case 3:
            StatisticsMenu(customers, employees);
            break;

        case 0:
            return 0;
        }
    }
}
