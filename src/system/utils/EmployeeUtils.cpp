#include <string>
#include "../core/Employee.h"
#include "../utils/EmployeeUtils.h"
#include "../core/customer.h"
#include "../core/Account.h"
#include "../core/TransactionStack.h"
#include "../core/LoanRequest.h"
#include "../core/LoanListMeth.h"
#include "../core/ArchivedAccount.h"
#include "../core/CompletedLoanListMeth.h"
#include "../core/LoanRequestQueueMeth.h"
using namespace std;


bool resizeEmployeeArray(EmployeeArray& employees) {
    int newCapacity = (employees.capacity == 0) ? 2 : employees.capacity * 2;
    Employee* newData = new (nothrow) Employee[newCapacity];
    if (!newData) {
        cout << "Memory allocation failed while resizing.\n";
        return false;
    }
    for (int i = 0; i < employees.size; i++) {
        newData[i] = employees.data[i];
    }
    delete[] employees.data;

    employees.data = newData;
    employees.capacity = newCapacity;
    return true;
}


EmployeeArray createEmployeeArray(int initialCapacity) {
    EmployeeArray arr;
    arr.size = 0;

    if (initialCapacity < 1) initialCapacity = 2;
    arr.capacity = initialCapacity;
    arr.data = new (nothrow) Employee[arr.capacity];

    if (!arr.data) {
        cerr << "Memory allocation failed for employee array.\n";
        arr.capacity = 0;
    }
    return arr;
}

void addEmployee(EmployeeArray& employees, const Employee& e) {
    if (employees.size == employees.capacity) {
        if (!resizeEmployeeArray(employees)) {
            cout << "Failed to add employee: memory allocation error.\n";
            return;
        }
    }
    employees.data[employees.size] = e;
    employees.size++;
    cout << "Employee added successfully.\n";
}

int deleteEmployee(EmployeeArray& employees, unsigned int id) {
    if (employees.size == 0) {
        cout << "No employees to delete.\n";
        return 0;
    }
    int index = -1;
	for (int i = 0; i < employees.size; i++) { //search in the whole array
        if (employees.data[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Employee with ID " << id << " not found.\n";
        return 0;
    }
    for (int i = index; i < employees.size - 1; i++) {
        employees.data[i] = employees.data[i + 1];
    }
    employees.size--;

    cout << "Employee deleted successfully.\n";
    return 1;
}

int modifyEmployee(EmployeeArray& employees, unsigned int id)
{
    if (employees.size == 0) {
        cout << "No employees to modify.\n";
        return 0;
    }
    for (int i = 0; i < employees.size; i++) {
        if (employees.data[i].id == id) {
			cout << "old information:\n";//display old information
			cout << "ID: " << employees.data[i].id << "\n";
			cout << "First Name: " << employees.data[i].name << "\n";
			cout << "Last Name: " << employees.data[i].lastName << "\n";
			cout << "Address: " << employees.data[i].address << "\n";
			cout << "Salary: " << employees.data[i].salary << "\n";
			cout << "Hire Date: " << employees.data[i].hireDate.day << "/"
                << employees.data[i].hireDate.month << "/"
				<< employees.data[i].hireDate.year << "\n";
			cout << "Branch Code: " << employees.data[i].branchCode << "\n";


            cout << "\n--- Modify Employee (ID: " << id << ") ---\n";

            cout << "Enter new first name: ";
            cin >> employees.data[i].name;

            cout << "Enter new last name: ";
            cin >> employees.data[i].lastName;

            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, employees.data[i].address);

            cout << "Enter new salary: ";
            cin >> employees.data[i].salary;

            cout << "Enter new hire date (day month year): ";
            cin >> employees.data[i].hireDate.day
                >> employees.data[i].hireDate.month
                >> employees.data[i].hireDate.year;

            cout << "Enter new branch code: ";
            cin >> employees.data[i].branchCode;

            cout << "Employee information updated successfully.\n";
            return 1;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
    return 0;
}

void displayEmployeesAlphabetically(const EmployeeArray& employees) {
    if (employees.size == 0) {
		cout << "No employees to display.\n";
    }
	Employee* sortedEmployees = new (nothrow) Employee[employees.size];
    for (int i = 0; i < employees.size; i++) {
        sortedEmployees[i] = employees.data[i];
	}
	for (int i = 0; i < employees.size - 1; i++) {//bubble sort on the copy array  so that we dont change the original array
        for (int j = 0; j < employees.size - i - 1; j++) {
            if (sorted[j].lastName > sorted[j + 1].lastName) {
                Employee temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    cout << "\n--- Employees in Alphabetical Order (by Last Name) ---\n";

    for (int i = 0; i < employees.size; i++)
    {
        cout << "\nEmployee #" << (i + 1) << endl;
        cout << "ID: " << sorted[i].id << endl;
        cout << "Name: " << sorted[i].name << endl;
        cout << "Last Name: " << sorted[i].lastName << endl;
        cout << "Address: " << sorted[i].address << endl;
        cout << "Salary: " << sorted[i].salary << endl;

        cout << "Hire Date: "
            << sorted[i].hireDate.day << "/"
            << sorted[i].hireDate.month << "/"
            << sorted[i].hireDate.year << endl;

        cout << "Branch Code: " << sorted[i].branchCode << endl;
        cout << "--------------------------------------\n";
    }
    delete[] sorted;
}

//function existInArray
bool existInArray(const int arr[], int e) {
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        if (arr[i] == e) {
            return true;
        }
	}
	return false;
}

void displayEmployeesByBranch(const EmployeeArray& employees) {
    if (employees.size == 0) {
        cout << "No employees to display.\n";
        return;
	}
    int AllBranches[50]; //bank has at most 50 branches
	int counter = 0;
    for (int i = 0; i < employees.size; i++) {
        if (!existInArray(AllBranches, employees.data[i].branchCode)) {
            AllBranches[counter] = employees.data[i].branchCode;
            counter++;
        }
    }
    for (int i = 0; i < counter; i++) {
        cout << "\n--- Employees in Branch " << AllBranches[i] << " ---\n";
        for (int j = 0; j < employees.size; j++) {
            if (employees.data[j].branchCode == AllBranches[i]) {
                cout << "\nEmployee ID: " << employees.data[j].id << endl;
                cout << "Name: " << employees.data[j].name << endl;
                cout << "Last Name: " << employees.data[j].lastName << endl;
                cout << "Address: " << employees.data[j].address << endl;
                cout << "Salary: " << employees.data[j].salary << endl;
                cout << "Hire Date: "
                    << employees.data[j].hireDate.day << "/"
                    << employees.data[j].hireDate.month << "/"
                    << employees.data[j].hireDate.year << endl;
                cout << "Branch Code: " << employees.data[j].branchCode << endl;
                cout << "--------------------------------------\n";
            }
        }
	}
}

void DisplayEarliestHiredEmployees(const EmployeeArray& employees) {
    if (employees.size == 0) {
        cout << "No employees to display.\n";
        return;
    }
    date earliestDate = employees.data[0].hireDate;
    for (int i = 1; i < employees.size; i++) {
        date currentDate = employees.data[i].hireDate;
        if (currentDate.year < earliestDate.year ||
            (currentDate.year == earliestDate.year && currentDate.month < earliestDate.month) ||
            (currentDate.year == earliestDate.year && currentDate.month == earliestDate.month && currentDate.day < earliestDate.day)) {
            earliestDate = currentDate;
        }
    }
    cout << "\n--- Earliest Hired Employees ---\n";
    for (int i = 0; i < employees.size; i++) {
        date currentDate = employees.data[i].hireDate;
        if (currentDate.day == earliestDate.day &&
            currentDate.month == earliestDate.month &&
            currentDate.year == earliestDate.year) {
            cout << "\nEmployee ID: " << employees.data[i].id << endl;
            cout << "Name: " << employees.data[i].name << endl;
            cout << "Last Name: " << employees.data[i].lastName << endl;
            cout << "Address: " << employees.data[i].address << endl;
            cout << "Salary: " << employees.data[i].salary << endl;
            cout << "Hire Date: "
                << employees.data[i].hireDate.day << "/"
                << employees.data[i].hireDate.month << "/"
                << employees.data[i].hireDate.year << endl;
            cout << "Branch Code: " << employees.data[i].branchCode << endl;
            cout << "--------------------------------------\n";
        }
	}
}

void DisplayMostRecentlyHiredEmployee(const EmployeeArray& employees) {
    if (employees.size == 0) {
        cout << "No employees to display.\n";
        return;
    }
    date latestDate = employees.data[0].hireDate;
    for (int i = 1; i < employees.size; i++) {
        date currentDate = employees.data[i].hireDate;
        if (currentDate.year > latestDate.year ||
            (currentDate.year == latestDate.year && currentDate.month > latestDate.month) ||
            (currentDate.year == latestDate.year && currentDate.month == latestDate.month && currentDate.day > latestDate.day)) {
            latestDate = currentDate;
        }
    }
    cout << "\n--- Most Recently Hired Employees ---\n";
    for (int i = 0; i < employees.size; i++) {
        date currentDate = employees.data[i].hireDate;
        if (currentDate.day == latestDate.day &&
            currentDate.month == latestDate.month &&
            currentDate.year == latestDate.year) {
            cout << "\nEmployee ID: " << employees.data[i].id << endl;
            cout << "Name: " << employees.data[i].name << endl;
            cout << "Last Name: " << employees.data[i].lastName << endl;
            cout << "Address: " << employees.data[i].address << endl;
            cout << "Salary: " << employees.data[i].salary << endl;
            cout << "Hire Date: "
                << employees.data[i].hireDate.day << "/"
                << employees.data[i].hireDate.month << "/"
                << employees.data[i].hireDate.year << endl;
            cout << "Branch Code: " << employees.data[i].branchCode << endl;
            cout << "--------------------------------------\n";
        }
	}
}

//this makes the account numbers unique by incrementing for each new account
static unsigned int nextAccountNumber = 1;

int AddCustomerAccount(CustomerList& list) {
    CustomerNode* newNode = new (nothrow) CustomerNode();
    if (!newNode) {
        cout << "Memory allocation failed.\n";
        return 0;
    }
    cout << "\n--- Add New Customer Account ---\n";
    cout << "Enter First Name: ";
    cin >> newNode->data.loginUsername;

    cout << "Enter Last Name: ";
    cin >> newNode->data.loginPassword;

    // --- Create Account Info ---
    Account acc;

    acc.Account_number = nextAccountNumber++;

    cout << "Enter Account Type (savings/current): ";
    cin >> acc.Account_type;

    cout << "Enter IBAN: ";
    cin >> acc.IBAN;

    cout << "Enter Branch Code: ";
    cin >> acc.Branch_code;

    acc.Account_holder_name = newNode->data.firstName + " " + newNode->data.lastName;

    cout << "Enter Opening Date (day month year): ";
    cin >> acc.Opening_date.day
        >> acc.Opening_date.month
        >> acc.Opening_date.year;

    acc.Status = "active";
    acc.Balance = 0;

    // Init loan list and transaction stack
    acc.loansHead = nullptr;
    acc.transactions = createTransactionStack();

    // Attach account to customer
    newNode->data.account = acc;

    // Insert into list (HEAD INSERTION)
    newNode->next = list.head;
    list.head = newNode;

    cout << "\nCustomer account created successfully.\n";
    cout << "Assigned Account Number: " << acc.Account_number << endl;
    return 1;
}

void DisplayAllAccounts(const CustomerList& list)
{
    if (list.head == nullptr) {
        cout << "No accounts to display.\n";
        return;
    }

    cout << "\n=========== LIST OF ALL ACCOUNTS ===========\n";

    CustomerNode* current = list.head;
    int count = 1;

    while (current != nullptr)
    {
        const Account& acc = current->data.account;

        cout << "\nAccount #" << count++ << endl;
        cout << "--------------------------------------------\n";
        cout << "Account Number   : " << acc.Account_number << endl;
        cout << "Account Type     : " << acc.Account_type << endl;
        cout << "IBAN             : " << acc.IBAN << endl;
        cout << "Branch Code      : " << acc.Branch_code << endl;
        cout << "Holder Name      : " << acc.Account_holder_name << endl;

        cout << "Opening Date     : "
            << acc.Opening_date.day << "/"
            << acc.Opening_date.month << "/"
            << acc.Opening_date.year << endl;

        cout << "Status           : " << acc.Status << endl;
        cout << "Balance          : " << acc.Balance << " TND" << endl;

        cout << "--------------------------------------------\n";

        current = current->next;
    }

    cout << "============================================\n";
}

void ChangeAccountStatus(CustomerList& list, int account_number) {
	CustomerNode* current = list.head;
    while (current != nullptr) {
        if (current->data.account.Account_number == account_number) {
            cout << "Current Status: " << current->data.account.Status << endl;
            cout << "Enter new status (active/inactive/closed): ";
            string newStatus;
            cin >> newStatus;
            current->data.account.Status = newStatus;
            cout << "Account status updated successfully.\n";
            return;
        }
        current = current->next;
    }
	cout << "Account with number " << account_number << " not found.\n";
}

void DeleteClosedAccounts(CustomerList& customers, ArchivedAccountArray& archived) {
    if (customers.head == nullptr) {
        cout << "No customers to check.\n";
        return;
    }
    CustomerNode* current = customers.head;
    CustomerNode* prev = nullptr;

    int deletedCount = 0;

    while (current != nullptr) {
        // Check if this account is closed
        if (current->data.account.Status == "closed") {
            // Save the account into archived array
            addArchivedAccount(archived, current->data.account);

            // Remove from the linked list
            if (prev == nullptr) {
                // removing head node
                customers.head = current->next;
            }
            else {
                prev->next = current->next;
            }

            // delete node
            CustomerNode* temp = current;
            current = current->next;
            delete temp;

            deletedCount++;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
    cout << "\n✔ " << deletedCount << " closed accounts were archived and removed.\n";
}

void ChangeLoanStatus(CustomerList& customers) {
    if (customers.head == nullptr) {
        cout << "No customers in the list.\n";
        return;
    }
    unsigned int accNumber;
    unsigned int loanID;
    string newStatus;
    cout << "\n--- Change Loan Status ---\n";
    cout << "Enter Account Number: ";
    cin >> accNumber;
    
    CustomerNode* customer = customers.head; //searching for the customer
    while (customer != nullptr && customer->data.account.Account_number != accNumber) {
        customer = customer->next;
    }
    if(customer == nullptr) {
        customer << "Account not found.\n";
        return;
    }

    cout << "Enter Loan ID: ";
    cin >> loanID;

    LoanNode* loanPtr = findLoan(cust->data.account.loansHead, loanID);
    if (loanPtr == nullptr) {
        cout << "Loan with ID " << loanID << " not found.\n";
        return;
    }
    cout << "\ncurrent state is : " << loanPtr->data.loanStatus << endl;
    cout << "Enter new status (active / pending / rejected / completed): ";
    cin >> newStatus;
    loanPtr->data.loanStatus = newStatus;
    
    cout << "Loan status updated successfully.\n";
}

void DeleteCompletedLoans(CustomerList& customers, CompletedLoanList*& completedList) {
    if (completedList == nullptr) {
        completedList = createCompletedLoanList();
    }

    if (customers.head == nullptr) {
        cout << "No customers available.\n";
        return;
    }
    CustomerNode* cust = customers.head;
    int deletedCount = 0;
    while (cust != nullptr) {
        LoanNode* current = cust->data.account.loansHead;
        LoanNode* prev = nullptr;

        while (current != nullptr) {
            if (current->data.loanStatus == "completed") {
                addCompletedLoan(*completedList, current->data);
                if (prev == nullptr) {
                    cust->data.account.loansHead = current->next;
                }
                else {
                    prev->next = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = prev;
                }
                LoanNode* temp = current;
                current = current->next;
                delete temp;

                deletedCount++;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        cust = cust->next;
    }
    cout << "\n" << deletedCount << " completed loans moved to completed loan list.\n";
}

//these 4 functions are used to simplify ManageLoanRequests
CustomerNode* findCustomerAccount(CustomerList& customers, unsigned int accountNumber) {
    CustomerNode* curr = customers.head;
    while (curr != nullptr) {
        if (curr->data.account.Account_number == accountNumber) return curr;
        curr = curr->next;
    }
    return nullptr; // not found
}

int AddLoanToCustomer(Customer* customer, const Loan& loan) {
    if (!customer) {
        cout << "Invalid customer.\n";
        return 0;
    }
    int result = insertLoan(&customer->account.loans, loan);
    if (result) {
        cout << "Loan added successfully to account "
            << customer->account.Account_number << endl;
    }
    else {
        cout << "Failed to add loan to this customer.\n";
    }
    return result;   // 1 = success, 0 = failure
}

void DeclineLoanRequest(const LoanRequest& request) {
    cout << "\nLoan Request DECLINED\n";
    cout << "Request ID: " << request.requestID << endl;
    cout << "Account Number: " << request.accountNumber << endl;
    cout << "Status: declined\n";
    cout << "This request has been permanently removed.\n";
}

void AcceptLoanRequest(CustomerList& customers, const LoanRequest& request) {
    CustomerNode* cust = findCustomerAccount(customers, request.accountNumber);
    if (!cust) {
        cout << "❌ Customer account not found. Cannot accept request.\n";
        return;
    }
    Loan newLoan;
    newLoan.ID = nextLoanID++;
    newLoan.loanType = request.loanType;
    newLoan.principalAmount = request.requestedAmount;
    newLoan.interestRate = request.interestRate;
    newLoan.amountPaid = 0;
    newLoan.remainingBalance = request.requestedAmount;
    newLoan.startDate = request.requestDate;
    newLoan.endDate = request.requestDate;
    newLoan.loanStatus = "active";

    if (addLoanToAccount(cust->data.account, newLoan)) {
        cout << "\nLoan request ACCEPTED.\n";
        cout << "Loan added to account " << request.accountNumber << ".\n";
    }
    else {
        cout << "Error: could not insert loan into account.\n";
    }
}

void ManageLoanRequests(CustomerList& customers, LoanRequestQueue* queue) {
    if (!queue || LoanRequestQueueEmpty(*queue)) {
        cout << "\nNo pending loan requests.\n";
        return;
    }

    cout << "\n========== MANAGING LOAN REQUESTS (FIFO) ==========\n";

    while (!LoanRequestQueueEmpty(*queue)) {
        cout << "\nProcessing next loan request...\n";

        LoanRequest req = dequeueLoanRequest(queue);

        printLoanRequest(req);

        char choice;
        cout << "\nAccept this loan request? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            AcceptLoanRequest(customers, req);
        }
        else {
            DeclineLoanRequest(req);
        }
    }
    cout << "\n✔ All loan requests have been processed.\n";
}

    
