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

bool resizeEmployeeArray(EmployeeArray &employees)
{
    int newCapacity = (employees.capacity == 0) ? 2 : employees.capacity * 2;
    Employee *newData = new (nothrow) Employee[newCapacity];
    if (!newData)
    {
        cout << "Memory allocation failed while resizing.\n";
        return false;
    }
    for (int i = 0; i < employees.size; i++)
    {
        newData[i] = employees.data[i];
    }
    delete[] employees.data;

    employees.data = newData;
    employees.capacity = newCapacity;
    return true;
}

EmployeeArray createEmployeeArray(int initialCapacity)
{
    EmployeeArray arr;
    arr.size = 0;

    if (initialCapacity < 1)
        initialCapacity = 2;
    arr.capacity = initialCapacity;
    arr.data = new (nothrow) Employee[arr.capacity];

    if (!arr.data)
    {
        cerr << "Memory allocation failed for employee array.\n";
        arr.capacity = 0;
    }
    return arr;
}

void addEmployee(EmployeeArray &employees, const Employee &e)
{
    if (employees.size == employees.capacity)
    {
        if (!resizeEmployeeArray(employees))
        {
            cout << "Failed to add employee: memory allocation error.\n";
            return;
        }
    }
    employees.data[employees.size] = e;
    employees.size++;
    cout << "Employee added successfully.\n";
}

int deleteEmployee(EmployeeArray &employees, unsigned int id)
{
    if (employees.size == 0)
    {
        cout << "No employees to delete.\n";
        return 0;
    }
    int index = -1;
    for (int i = 0; i < employees.size; i++)
    { // search in the whole array
        if (employees.data[i].Id == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Employee with ID " << id << " not found.\n";
        return 0;
    }
    for (int i = index; i < employees.size - 1; i++)
    {
        employees.data[i] = employees.data[i + 1];
    }
    employees.size--;

    cout << "Employee deleted successfully.\n";
    return 1;
}

int modifyEmployee(EmployeeArray &employees, unsigned int id)
{
    if (employees.size == 0)
    {
        cout << "No employees to modify.\n";
        return 0;
    }
    for (int i = 0; i < employees.size; i++)
    {
        if (employees.data[i].Id == id)
        {
            cout << "old information:\n"; // display old information
            cout << "ID: " << employees.data[i].Id << "\n";
            cout << "First Name: " << employees.data[i].Name << "\n";
            cout << "Last Name: " << employees.data[i].Last_name << "\n";
            cout << "Address: " << employees.data[i].Address << "\n";
            cout << "Salary: " << employees.data[i].salary << "\n";
            cout << "Hire Date: " << employees.data[i].Hire_date.day << "/"
                 << employees.data[i].Hire_date.month << "/"
                 << employees.data[i].Hire_date.year << "\n";
            cout << "Branch Code: " << employees.data[i].Bank_branch << "\n";

            cout << "\n--- Modify Employee (ID: " << id << ") ---\n";

            cout << "Enter new first name: ";
            cin >> employees.data[i].Name;

            cout << "Enter new last name: ";
            cin >> employees.data[i].Last_name;

            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, employees.data[i].Address);

            cout << "Enter new salary: ";
            cin >> employees.data[i].salary;

            cout << "Enter new hire date (day month year): ";
            cin >> employees.data[i].Hire_date.day >> employees.data[i].Hire_date.month >> employees.data[i].Hire_date.year;

            cout << "Enter new branch code: ";
            cin >> employees.data[i].Bank_branch;

            cout << "Employee information updated successfully.\n";
            return 1;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
    return 0;
}

void displayEmployeesAlphabetically(const EmployeeArray &employees)
{
    if (employees.size == 0)
    {
        cout << "No employees to display.\n";
    }
    Employee *sortedEmployees = new (nothrow) Employee[employees.size];
    for (int i = 0; i < employees.size; i++)
    {
        sortedEmployees[i] = employees.data[i];
    }
    for (int i = 0; i < employees.size - 1; i++)
    { // bubble sort on the copy array  so that we dont change the original array
        for (int j = 0; j < employees.size - i - 1; j++)
        {
            if (sortedEmployees[j].Last_name > sortedEmployees[j + 1].Last_name)
            {
                Employee temp = sortedEmployees[j];
                sortedEmployees[j] = sortedEmployees[j + 1];
                sortedEmployees[j + 1] = temp;
            }
        }
    }
    cout << "\n--- Employees in Alphabetical Order (by Last Name) ---\n";

    for (int i = 0; i < employees.size; i++)
    {
        cout << "\nEmployee #" << (i + 1) << endl;
        cout << "ID: " << sortedEmployees[i].Id << endl;
        cout << "Name: " << sortedEmployees[i].Name << endl;
        cout << "Last Name: " << sortedEmployees[i].Last_name << endl;
        cout << "Address: " << sortedEmployees[i].Address << endl;
        cout << "Salary: " << sortedEmployees[i].salary << endl;

        cout << "Hire Date: "
             << sortedEmployees[i].Hire_date.day << "/"
             << sortedEmployees[i].Hire_date.month << "/"
             << sortedEmployees[i].Hire_date.year << endl;

        cout << "Branch Code: " << sortedEmployees[i].Bank_branch << endl;
        cout << "--------------------------------------\n";
    }
    delete[] sortedEmployees;
}

// function existInArray
bool existInArray(const unsigned int arr[], unsigned int e)
{
    for (int i = 0; i < 50; i++)
    {
        if (arr[i] == e)
        {
            return true;
        }
    }
    return false;
}

void displayEmployeesByBranch(const EmployeeArray &employees)
{
    if (employees.size == 0)
    {
        cout << "No employees to display.\n";
        return;
    }
    unsigned int AllBranches[50]; // bank has at most 50 branches
    int counter = 0;
    for (int i = 0; i < employees.size; i++)
    {
        if (!existInArray(AllBranches, employees.data[i].Bank_branch))
        {
            AllBranches[counter] = employees.data[i].Bank_branch;
            counter++;
        }
    }
    for (int i = 0; i < counter; i++)
    {
        cout << "\n--- Employees in Branch " << AllBranches[i] << " ---\n";
        for (int j = 0; j < employees.size; j++)
        {
            if (employees.data[j].Bank_branch == AllBranches[i])
            {
                cout << "\nEmployee ID: " << employees.data[j].Id << endl;
                cout << "Name: " << employees.data[j].Name << endl;
                cout << "Last Name: " << employees.data[j].Last_name << endl;
                cout << "Address: " << employees.data[j].Address << endl;
                cout << "Salary: " << employees.data[j].salary << endl;
                cout << "Hire Date: "
                     << employees.data[j].Hire_date.day << "/"
                     << employees.data[j].Hire_date.month << "/"
                     << employees.data[j].Hire_date.year << endl;
                cout << "Branch Code: " << employees.data[j].Bank_branch << endl;
                cout << "--------------------------------------\n";
            }
        }
    }
}

void DisplayEarliestHiredEmployees(const EmployeeArray &employees)
{
    if (employees.size == 0)
    {
        cout << "No employees to display.\n";
        return;
    }
    date earliestDate = employees.data[0].Hire_date;
    for (int i = 1; i < employees.size; i++)
    {
        date currentDate = employees.data[i].Hire_date;
        if (currentDate.year < earliestDate.year ||
            (currentDate.year == earliestDate.year && currentDate.month < earliestDate.month) ||
            (currentDate.year == earliestDate.year && currentDate.month == earliestDate.month && currentDate.day < earliestDate.day))
        {
            earliestDate = currentDate;
        }
    }
    cout << "\n--- Earliest Hired Employees ---\n";
    for (int i = 0; i < employees.size; i++)
    {
        date currentDate = employees.data[i].Hire_date;
        if (currentDate.day == earliestDate.day &&
            currentDate.month == earliestDate.month &&
            currentDate.year == earliestDate.year)
        {
            cout << "\nEmployee ID: " << employees.data[i].Id << endl;
            cout << "Name: " << employees.data[i].Name << endl;
            cout << "Last Name: " << employees.data[i].Last_name << endl;
            cout << "Address: " << employees.data[i].Address << endl;
            cout << "Salary: " << employees.data[i].salary << endl;
            cout << "Hire Date: "
                 << employees.data[i].Hire_date.day << "/"
                 << employees.data[i].Hire_date.month << "/"
                 << employees.data[i].Hire_date.year << endl;
            cout << "Branch Code: " << employees.data[i].Bank_branch << endl;
            cout << "--------------------------------------\n";
        }
    }
}

void DisplayMostRecentlyHiredEmployee(const EmployeeArray &employees)
{
    if (employees.size == 0)
    {
        cout << "No employees to display.\n";
        return;
    }
    date latestDate = employees.data[0].Hire_date;
    for (int i = 1; i < employees.size; i++)
    {
        date currentDate = employees.data[i].Hire_date;
        if (currentDate.year > latestDate.year ||
            (currentDate.year == latestDate.year && currentDate.month > latestDate.month) ||
            (currentDate.year == latestDate.year && currentDate.month == latestDate.month && currentDate.day > latestDate.day))
        {
            latestDate = currentDate;
        }
    }
    cout << "\n--- Most Recently Hired Employees ---\n";
    for (int i = 0; i < employees.size; i++)
    {
        date currentDate = employees.data[i].Hire_date;
        if (currentDate.day == latestDate.day &&
            currentDate.month == latestDate.month &&
            currentDate.year == latestDate.year)
        {
            cout << "\nEmployee ID: " << employees.data[i].Id << endl;
            cout << "Name: " << employees.data[i].Name << endl;
            cout << "Last Name: " << employees.data[i].Last_name << endl;
            cout << "Address: " << employees.data[i].Address << endl;
            cout << "Salary: " << employees.data[i].salary << endl;
            cout << "Hire Date: "
                 << employees.data[i].Hire_date.day << "/"
                 << employees.data[i].Hire_date.month << "/"
                 << employees.data[i].Hire_date.year << endl;
            cout << "Branch Code: " << employees.data[i].Bank_branch << endl;
            cout << "--------------------------------------\n";
        }
    }
}

// this makes the account numbers unique by incrementing for each new account
static unsigned int nextAccountNumber = 0;

bool IsAlphabetic(const string &str)
{
    for (char c : str)
    {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ')))
        {
            return false;
        }
    }
    return true;
}

int AddCustomerAccount(CustomerList *&list)
{
    cout << "\n--- Add New Customer Account ---\n";
    cout << "Enter First Name: " << endl;
    string firstname;
    cin >> firstname;
    while (!IsAlphabetic(firstname))
    {
        cout << "Enter First Name: " << endl;
        cin >> firstname;
    }
    cout << "Enter Last Name: " << endl;
    string lastname;
    cin >> lastname;
    while (!IsAlphabetic(lastname))
    {
        cout << "Enter Last Name: " << endl;
        cin >> lastname;
    }
    cout << "Enter Username: " << endl;
    string username;
    cin >> username;

    cout << "Enter Password: " << endl;
    string password;
    cin >> password;

    // --- Create Account Info ---
    Account *acc = new (nothrow) Account;
    if (!acc)
    {
        cerr << "Memory allocation failed for Account\n";
        return 0;
    }

    acc->Account_number = nextAccountNumber++;

    cout << "Enter Account Type (savings/current): ";
    cin >> acc->Account_type;
    while (acc->Account_type != "savings" && acc->Account_type != "current")
    {
        cout << "Enter Account Type (savings/current): ";
        cin >> acc->Account_type;
    }
    cout << "Enter IBAN: ";
    cin >> acc->IBAN;

    cout << "Enter Branch Code: ";
    cin >> acc->Branch_code;
    // BONUS FIX FOR INVALID NON-INT INPUT
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid input! Please enter a number: ";
        cin >> acc->Branch_code;
    }

    acc->Account_holder_name = firstname + " " + lastname;

    cout << "Enter Opening Date (day month year): ";
    cin >> acc->Opening_date.day >> acc->Opening_date.month >> acc->Opening_date.year;

    acc->Status = "active";
    acc->Balance = 0;

    // Init loan list and transaction stack
    acc->loans = createLoanList();
    acc->transactions = createTransactionStack();

    Customer *data = new (nothrow) Customer{
        username,
        password,
        acc};
    if (!data)
    {
        cout << "Memory allocation failed.\n";
        return 0;
    }

    CustomerNode *newNode = new (nothrow) CustomerNode{
        data,
        nullptr};
    if (!newNode)
    {
        cout << "Memory allocation failed.\n";
        return 0;
    }

    // Attach account to customer
    newNode->data->account = acc;
    newNode->data->loginUsername = username;
    newNode->data->loginPassword = password;
    // Insert into list (HEAD INSERTION)
    newNode->next = list->head;
    list->head = newNode;

    cout << "\nCustomer account created successfully.\n";
    cout << "Assigned Account Number: " << acc->Account_number << endl;
    return 1;
}

void DisplayAllAccounts(CustomerList *&list)
{
    if (list->head == nullptr)
    {
        cout << "No accounts to display.\n";
        return;
    }

    cout << "\n=========== LIST OF ALL ACCOUNTS ===========\n";

    CustomerNode *current = list->head;
    int count = 1;

    while (current != nullptr)
    {
        const Account *acc = current->data->account;

        cout << "\nAccount #" << count++ << endl;
        cout << "--------------------------------------------\n";
        cout << "Account Number   : " << acc->Account_number << endl;
        cout << "Account Type     : " << acc->Account_type << endl;
        cout << "IBAN             : " << acc->IBAN << endl;
        cout << "Branch Code      : " << acc->Branch_code << endl;
        cout << "Holder Name      : " << acc->Account_holder_name << endl;

        cout << "Opening Date     : "
             << acc->Opening_date.day << "/"
             << acc->Opening_date.month << "/"
             << acc->Opening_date.year << endl;

        cout << "Status           : " << acc->Status << endl;
        cout << "Balance          : " << acc->Balance << " TND" << endl;

        cout << "--------------------------------------------\n";

        current = current->next;
    }

    cout << "============================================\n";
}

void ChangeAccountStatus(CustomerList *list, unsigned int account_number)
{
    CustomerNode *current = list->head;
    while (current != nullptr)
    {
        if (current->data->account->Account_number == account_number)
        {
            cout << "Current Status: " << current->data->account->Status << endl;
            cout << "Enter new status (active/inactive/closed): ";
            string newStatus;
            cin >> newStatus;
            current->data->account->Status = newStatus;
            cout << "Account status updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Account with number " << account_number << " not found.\n";
}

void DeleteClosedAccounts(CustomerList *customers, ArchivedAccountArray &archived)
{
    if (customers->head == nullptr)
    {
        cout << "No customers to check.\n";
        return;
    }
    CustomerNode *current = customers->head;
    CustomerNode *prev = nullptr;

    int deletedCount = 0;

    while (current != nullptr)
    {
        // Check if this account is closed
        if (current->data->account->Status == "closed")
        {
            // Save the account into archived array
            addArchivedAccount(archived, current->data->account);

            // Remove from the linked list
            if (prev == nullptr)
            {
                // removing head node
                customers->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            // delete node
            CustomerNode *temp = current;
            current = current->next;
            delete temp;

            deletedCount++;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    cout << "\n✔ " << deletedCount << " closed accounts were archived and removed.\n";
}

void ChangeLoanStatus(CustomerList *customers)
{
    if (customers->head == nullptr)
    {
        cout << "No customers in the list.\n";
        return;
    }
    unsigned int accNumber;
    unsigned int loanID;
    string newStatus;
    cout << "\n--- Change Loan Status ---\n";
    cout << "Enter Account Number: ";
    cin >> accNumber;

    CustomerNode *customer = customers->head; // searching for the customer
    while (customer != nullptr && customer->data->account->Account_number != accNumber)
    {
        customer = customer->next;
    }
    if (customer == nullptr)
    {
        cerr << "Account not found.\n";
        return;
    }

    cout << "Enter Loan ID: ";
    cin >> loanID;

    LoanNode *loanPtr = findLoan(customer->data->account->loans->head, loanID);
    if (loanPtr == nullptr)
    {
        cout << "Loan with ID " << loanID << " not found.\n";
        return;
    }
    cout << "\ncurrent state is : " << loanPtr->data.Loan_Status << endl;
    cout << "Enter new status (active / pending / rejected / completed): ";
    cin >> newStatus;
    loanPtr->data.Loan_Status = newStatus;

    cout << "Loan status updated successfully.\n";
}

void DeleteCompletedLoans(CustomerList *customers, CompletedLoanList *&completedList)
{
    if (completedList == nullptr)
    {
        completedList = createCompletedLoanList();
    }

    if (customers->head == nullptr)
    {
        cout << "No customers available.\n";
        return;
    }
    CustomerNode *cust = customers->head;
    int deletedCount = 0;
    while (cust != nullptr)
    {
        LoanNode *current = cust->data->account->loans->head;
        LoanNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->data.Loan_Status == "completed")
            {
                addCompletedLoan(*completedList, current->data);
                if (prev == nullptr)
                {
                    cust->data->account->loans->head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = prev;
                }
                LoanNode *temp = current;
                current = current->next;
                delete temp;

                deletedCount++;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        cust = cust->next;
    }
    cout << "\n"
         << deletedCount << " completed loans moved to completed loan list.\n";
}

// these 4 functions are used to simplify ManageLoanRequests
CustomerNode *findCustomerAccount(CustomerList *customers, unsigned int accountNumber)
{
    CustomerNode *curr = customers->head;
    while (curr != nullptr)
    {
        if (curr->data->account->Account_number == accountNumber)
            return curr;
        curr = curr->next;
    }
    return nullptr; // not found
}

int AddLoanToCustomer(Customer *customer, const Loan &loan)
{
    int result = insertLoan(customer->account->loans, loan);
    if (result)
    {
        cout << "Loan added successfully to account "
             << customer->account->Account_number << endl;
    }
    else
    {
        cout << "Failed to add loan to this customer.\n";
    }
    return result; // 1 = success, 0 = failure
}

void DeclineLoanRequest(const LoanRequest &request)
{
    cout << "\nLoan Request DECLINED\n";
    cout << "Request ID: " << request.requestID << endl;
    cout << "Account Number: " << request.accountNumber << endl;
    cout << "Status: declined\n";
    cout << "This request has been permanently removed.\n";
}

void AcceptLoanRequest(CustomerList *customers, const LoanRequest &request)
{
    CustomerNode *cust = findCustomerAccount(customers, request.accountNumber);
    if (!cust)
    {
        cout << "❌ Customer account not found. Cannot accept request.\n";
        return;
    }
    Loan newLoan;
    int nextLoanID = 1;
    LoanNode *temp = findLoan(cust->data->account->loans->head, nextLoanID);
    while (temp)
    {
        nextLoanID++;
        temp = findLoan(cust->data->account->loans->head, nextLoanID);
    }
    delete temp;
    newLoan.ID = nextLoanID;
    newLoan.Loan_type = request.loanType;
    newLoan.Principal_Amount = request.requestedAmount;
    newLoan.Interest_Rate = request.interestRate;
    newLoan.Amount_Paid = 0;
    newLoan.Remaining_Balance = request.requestedAmount;
    newLoan.Start_Date = request.requestDate;
    newLoan.End_Date = request.requestDate;
    newLoan.Loan_Status = "active";

    if (AddLoanToCustomer(cust->data, newLoan))
    {
        cout << "\nLoan request ACCEPTED.\n";
        cout << "Loan added to account " << request.accountNumber << ".\n";
    }
    else
    {
        cout << "Error: could not insert loan into account.\n";
    }
}

void ManageLoanRequests(CustomerList *customers, LoanRequestQueue *queue)
{
    if (!queue || LoanRequestQueueEmpty(*queue))
    {
        cout << "\nNo pending loan requests.\n";
        return;
    }

    cout << "\n========== MANAGING LOAN REQUESTS (FIFO) ==========\n";

    while (!LoanRequestQueueEmpty(*queue))
    {
        cout << "\nProcessing next loan request...\n";

        LoanRequest req = dequeueLoanRequest(queue);

        printLoanRequest(req);

        char choice;
        cout << "\nAccept this loan request? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            AcceptLoanRequest(customers, req);
        }
        else
        {
            DeclineLoanRequest(req);
        }
    }
    cout << "\n✔ All loan requests have been processed.\n";
}
