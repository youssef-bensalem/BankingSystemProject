// main.cpp
#include <iostream>
#include "include/system/Menu.h"
#include "include/core/Customer.h"
#include "include/core/Employee.h"
#include "include/core/LoanRequest.h"
#include "include/core/Transaction.h"
#include "include/utils/Date.h"
#include "include/system/DailyLog.h" // optional if you created DailyLog.h

using namespace std;

// Global containers (initialized in main)
CustomerList customers;
EmployeeArray employees;
LoanRequestQueue* requestQueue = nullptr;
DailyLog* dailyLog = nullptr; // optional: only if you implemented DailyLog

int main() {
    // initialize containers
    customers.head = nullptr;

    employees.data = nullptr;
    employees.size = 0;
    employees.capacity = 0;

    requestQueue = createLoanRequestQueue();
    // createDailyLog() must exist; if not, set dailyLog = nullptr
    dailyLog = createDailyLog();

    int choice;
    while (true) {
        cout << "\n";
        cout << " -------------------------------------------------------------------\n";
        cout << "|                   Welcome to the Banking Management System        |\n";
        cout << " -------------------------------------------------------------------\n";
        cout << "|                                                                   |\n";
        cout << "|                     1 - Customer interface                        |\n";
        cout << "|                     2 - Employee interface                        |\n";
        cout << "|                     3 - Exit                                      |\n";
        cout << "|                                                                   |\n";
        cout << " -------------------------------------------------------------------\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                CustomerMenu(customers, requestQueue);
                break;

            case 2:
                EmployeeMenu(customers, employees, requestQueue, dailyLog);
                break;

            case 3:
                cout << "Exiting system...\n";
                // cleanup
                if (requestQueue) destroyLoanRequestQueue(requestQueue);
                // TODO: destroy dailyLog if you added destroyDailyLog()
                return 0;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}


