#include "core/Customer.h"
#include "core/LoanRequest.h"
#include "core/LoanListMeth.h"
#include "core/LoanRequestQueueMeth.h"
#include "core/TransactionStackMeth.h"
#include <string>
using namespace std;

void createCustomerList(CustomerList* &list) {
    list = new (nothrow) CustomerList {
        nullptr
    };
    if (!list) cerr << "Memory allocation failed for CustomerList\n";
}

bool CustomerLogin(CustomerList* &customers, Customer* &loggedInCustomer)
{
    string username, password;

    cout << "\n===== CUSTOMER LOGIN =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    CustomerNode* current = customers->head;

    while (current != nullptr)
    {
        if (current->data->loginUsername == username &&
            current->data->loginPassword == password)
        {
            loggedInCustomer = current->data;
            cout << "\nLogin successful. Welcome " 
                 << loggedInCustomer->loginUsername << "!\n";
            return true;
        }
        current = current->next;
    }

    cout << "\nInvalid credentials. Try again.\n";
    return false;
}

void DisplayLoansByCustomer(Customer* customer) {
    if (!customer) {
        cout << "Invalid customer pointer.\n";
        return;
    }

    LoanNode* current = customer->account->loans->head;

    if (!current) {
        cout << "This customer has no loans.\n";
        return;
    }

    cout << "\n--- Loans for Customer: "
        << customer->account->Account_holder_name
        << " (Account " << customer->account->Account_number << ") ---\n";

    while (current != nullptr) {
        printLoan(&current->data);
        cout << "---------------------------\n";
        current = current->next;
    }
}

int SubmitLoanRequest(Customer* customer, LoanRequestQueue* queue) {
    if (!customer || !queue) {
        return -1;
    }

    if (customer->account->Status != "active") {
        return -2;
    }

    LoanRequest request;

    request.requestID = rand();
    request.accountNumber = customer->account->Account_number;

    cout << "\n--- Loan Request Submission ---\n";

    cout << "Loan type (car/home/business/student): ";
    cin >> request.loanType;

    cout << "Requested amount: ";
    cin >> request.requestedAmount;

    cout << "Interest rate: ";
    cin >> request.interestRate;

    cout << "Duration (months): ";
    cin >> request.durationMonths;

    cout << "Enter request date (day month year): ";
    cin >> request.requestDate.day
        >> request.requestDate.month
        >> request.requestDate.year;

    request.status = "pending";

    int ok = enqueueLoanRequest(queue, request);
    if (ok == 0) {
        return 0;
    }

    return 1;
}

int WithdrawMoney(Account* account) {
    if (!account) {
        cout << "Error: Invalid account.\n";
        return -1;
    }
    if (account->Status != "active") {
        cout << "Withdrawal denied: Account is not active.\n";
        return -2;
    }

    unsigned int amount;
    cout << "\nEnter amount to withdraw (10, 20, 50 TND): ";
    cin >> amount;
    
    if (amount % 10 != 0) {
        cout << "Withdrawal denied: Invalid denomination (amount must be divisible by 10).\n";
        return 0;
	}
    if (amount <= 0) {
        cout << "Withdrawal denied: Invalid amount.\n";
        return 0;
    }
    if (account->Balance < amount) {
        cout << "Withdrawal denied: Insufficient balance.\n";
        return 0;
    }

    account->Balance -= amount;

    date d;
    cout << "Enter transaction date (dd mm yyyy): ";
    cin >> d.day >> d.month >> d.year;

    Transaction t = createTransaction(
        account->Account_number,
        "withdrawal",
        amount,
        d);
    StackNode* node = createTransactionNode(t);
    if (!node) {
        cout << "Withdrawal failed: Could not allocate transaction node.\n";
        account->Balance += amount;
        return -3;
    }

    int ok = pushTransaction(account->transactions, node);
    if (!ok) {
        cout << "Withdrawal failed: Stack full.\n";
        account->Balance += amount;
        delete node;
        return 0;
    }

    cout << "Withdrawal successful.\n"
        << "Amount withdrawn: " << amount << " TND\n"
        << "New balance: " << account->Balance << " TND\n";

    return 1; // success
}

int DepositMoney(Account* account) {
    if (!account) {
        cout << "Error: Invalid account.\n";
        return -1;
    }
    if (account->Status != "active") {
        cout << "Deposit denied: Account is not active.\n";
        return -2;
    }

    double amount;
    cout << "\nEnter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Deposit denied: Invalid amount.\n";
        return 0;
    }
    date d;
    cout << "Enter transaction date (dd mm yyyy): ";
    cin >> d.day >> d.month >> d.year;

    account->Balance += amount;

    Transaction t = createTransaction(
        account->Account_number,
        "deposit",
        amount,
        d);
    StackNode* node = createTransactionNode(t);
    if (!node) {
        cout << "Deposit failed: Could not allocate transaction node.\n";
		account->Balance -= amount;//remove the amount
        return -3;
    }

    int ok = pushTransaction(account->transactions, node);
    if (!ok) {
        cout << "Deposit failed: Transaction stack is full.\n";
        account->Balance -= amount;//remove the amount
        delete node;
        return 0;
    }
    cout << "Deposit successful.\n"
        << "Amount deposited: " << amount << " TND\n"
        << "New balance: " << account->Balance << " TND\n";
    return 1; // success
}

void DisplayTodayTransactions(Account* account) {
    if (!account) {
        cout << "Error: Invalid account.\n";
        return;
    }
    if (!account->transactions || account->transactions->top == nullptr) {
        cout << "No transactions available for this account.\n";
        return;
    }

    date today;
    cout << "Enter today's date (dd mm yyyy): ";
    cin >> today.day >> today.month >> today.year;
    cout << "\n--- Transactions for "<< today.day << "/" << today.month << "/" << today.year<< " ---\n";
    StackNode* current = account->transactions->top;
    bool correctDay = false;

    while (current != nullptr) {
        Transaction& t = current->transaction;
        if (t.Date.day == today.day &&
            t.Date.month == today.month &&
            t.Date.year == today.year){

            cout << "\nTransaction ID: " << t.Transaction_ID << endl;
            cout << "Type: " << t.Type << endl;
            cout << "Amount: " << t.Amount << endl;
            cout << "Date: "
                << t.Date.day << "/"
                << t.Date.month << "/"
                << t.Date.year << endl;
            cout << "-------------------------\n";

            correctDay = true;
        }
        current = current->next;
    }
    if (!correctDay) {
        cout << "No transactions found for this date.\n";
    }
}

int UndoLastTransaction(Account* account) {
    if (!account) {
        cout << "Error: Invalid account.\n";
        return -1;
    }
    if (!account->transactions) {
        cout << "Error: Transaction stack not initialized.\n";
        return -2;
    }
    if (isTransactionStackEmpty(account->transactions)) {
        cout << "No transactions to undo.\n";
        return 0;
    }

    StackNode* node = account->transactions->top;
    account->transactions->top = node->next;

    Transaction t = node->transaction;
    delete node;

    if (t.Type == "deposit") {//DEPOSIT
        account->Balance -= t.Amount;
        cout << "Last deposit undone.\n";
    }
	else if (t.Type == "withdrawal") {//WITHDRAWAL
        account->Balance += t.Amount;
        cout << "Last withdrawal undone.\n";
    }
    cout << "New balance (after undoing): " << account->Balance << " TND\n";

    return 1; // success
}
