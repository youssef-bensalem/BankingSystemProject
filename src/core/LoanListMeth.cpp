#include "core/LoanNode.h"
#include "core/LoanListMeth.h"
#include <iostream>
using namespace std;

LoanNode *createLoanNode(const Loan &loan)
{
    LoanNode *newNode = new (nothrow) LoanNode();
    if (!newNode)
    {
        cerr << "Memory allocation failed for LoanNode." << endl;
        return nullptr;
    }
    newNode->data = loan;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

LoanList *createLoanList()
{

    LoanList *list = new (nothrow) LoanList
    {
        nullptr,
        nullptr,
        0
    };
    if (!list) {
        cerr << "Memory allocation failed for LoanList.\n";
    }
    return list;
}

void destroyLoanList(LoanList *list)
{
    if (!list)
        return;
    LoanNode *current = list->head;
    while (current != nullptr)
    {
        LoanNode *temp = current;
        current = current->next;
        delete temp;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    delete list;
}

int insertLoan(LoanList *list, const Loan &loan)
{
    if (!list)
    {
        return 0;
    }
    LoanNode *newNode = createLoanNode(loan);
    if (!newNode)
    {
        return 0;
    }
    if (LoanListEmpty(*list))
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
    return 1;
}

bool LoanListEmpty(const LoanList &list)
{
    return list.size == 0;
}

bool LoanListFull(LoanList &list)
{
    LoanNode *testNode = new (nothrow) LoanNode();
    if (!testNode)
    {
        return true;
    }
    delete testNode;
    return false;
}

int removeLoan(LoanList *list, unsigned int ID)
{
    if (!list || LoanListEmpty(*list))
    {
        cerr << "Loan list is empty. Cannot remove loan." << endl;
        return 0;
    }

    LoanNode *prev = nullptr;
    LoanNode *current = list->head;

    while (current != nullptr && current->data.ID != ID)
    {
        prev = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cerr << "Loan with ID " << ID << " not found." << endl;
        return 0;
    }

    if (prev == nullptr)
    {
        list->head = current->next;
        if (list->head != nullptr)
        {
            list->head->prev = nullptr;
        }
    }
    else
    {
        prev->next = current->next;
        if (current->next != nullptr)
        {
            current->next->prev = prev;
        }
    }

    if (current == list->tail)
    {
        list->tail = prev;
    }

    delete current;
    list->size--;
    return 1;
}

int countLoans(const LoanList &list)
{
    return list.size;
}

LoanNode *findLoan(LoanNode *head, unsigned int loanID)
{
    LoanNode *current = head;
    while (current != nullptr)
    {
        if (current->data.ID == loanID)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void printLoan(const Loan *loan)
{
    if (!loan)
    {
        cout << "Loan not found.\n";
        return;
    }

    cout << "\n--- Loan Details ---\n";
    cout << "Loan ID: " << loan->ID << endl;
    cout << "Type: " << loan->Loan_type << endl;
    cout << "Principal: " << loan->Principal_Amount << endl;
    cout << "Interest Rate: " << loan->Interest_Rate << "%" << endl;
    cout << "Amount Paid: " << loan->Amount_Paid << endl;
    cout << "Remaining Balance: " << loan->Remaining_Balance << endl;

    cout << "Start Date: "
         << loan->Start_Date.day << "/"
         << loan->Start_Date.month << "/"
         << loan->Start_Date.year << endl;

    cout << "End Date: "
         << loan->End_Date.day << "/"
         << loan->End_Date.month << "/"
         << loan->End_Date.year << endl;

    cout << "Status: " << loan->Loan_Status << endl;
}

void printAllLoans(const LoanList *list)
{
    if (!list || list->head == nullptr)
    {
        cout << "No loans to display.\n";
        return;
    }

    LoanNode *current = list->head;
    while (current != nullptr)
    {
        printLoan(&current->data);
        cout << "---------------------\n";
        current = current->next;
    }
}

int updateLoanPayment(LoanList *list, unsigned int loanID, double paymentAmount)
{
    if (!list)
    {
        return 0;
    }

    LoanNode *loanNode = findLoan(list->head, loanID);
    if (!loanNode)
    {
        return 0;
    }

    Loan *loan = &(loanNode->data);
    loan->Amount_Paid += paymentAmount;
    loan->Remaining_Balance -= paymentAmount;

    if (loan->Remaining_Balance < 0)
    {
        loan->Remaining_Balance = 0;
    }

    return 1;
}
