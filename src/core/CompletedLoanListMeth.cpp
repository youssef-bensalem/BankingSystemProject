#include "core/CompletedLoanListMeth.h"
#include <string>
#include <iostream>
using namespace std;

CompletedLoanList* createCompletedLoanList() {
    CompletedLoanList* list = new (nothrow) CompletedLoanList;

    if (!list) {
        cerr << "\nMemory allocation failed for completed loan list\n";
        return nullptr;
    }

    list->head = nullptr;

    return list;
}


void destroyCompletedLoanList(CompletedLoanList* list) {
    CompletedLoanNode* curr = list->head;
    while (curr) {
        CompletedLoanNode* next = curr->next;
        delete curr;
        curr = next;
    }
    delete list;
};

CompletedLoanNode* createCompletedLoan(const Loan& loan) {
    CompletedLoanNode* completed_loan_node = new (nothrow) CompletedLoanNode{
        loan,
        nullptr
    };

    if (!completed_loan_node) {
        cerr << "\nMemory allocation failed for completed loan node\n";
    };

    return completed_loan_node;
};

void destroyCompletedLoan(CompletedLoanNode* node) {
    delete node;
};

int findCompletedLoan(const CompletedLoanList* list, Loan loan) {
    if (list->head == nullptr) return -1;

    CompletedLoanNode* node = list->head;
    int index = 0;

    while (node) {
        if (node->data.ID == loan.ID) return index;
        node = node->next;
        index++;
    };

    return -1;
};

int addCompletedLoan(CompletedLoanList& list, const Loan& loan) {
    CompletedLoanNode* newNode = new (nothrow) CompletedLoanNode();
    if (!newNode) {
        cout << "Memory allocation failed for completed loan.\n";
        return 0;
    }

    newNode->data = loan;
    newNode->next = list.head;
    list.head = newNode;
    return 1;
}

int removeCompletedLoan(CompletedLoanList* list, unsigned int loanID) {
    if (list->head == nullptr) return 1; // empty

    CompletedLoanNode* curr = list->head;
    CompletedLoanNode* prev = nullptr;

    while (curr) {
        if (curr->data.ID == loanID) {
            if (prev == nullptr) {
                list->head = curr->next;
            }
            else {
                prev->next = curr->next;
            };

            if (curr == list->tail)
                list->tail = prev;

            delete curr;
            list->size--;
            return 0;
        };

        prev = curr;
        curr = curr->next;
    };

    return 1; // not found
};

int countCompletedLoans(const CompletedLoanList* list) {
    return list->size;
};

void printCompletedLoan(const CompletedLoanNode* node) {
    cout << "Loan ID: " << node->data.ID << endl;
};

void printAllCompletedLoans(const CompletedLoanList* list) {
    CompletedLoanNode* node = list->head;
    while (node) {
        printCompletedLoan(node);
        node = node->next;
    };
};

bool isCompletedLoanListEmpty(const CompletedLoanList* list) {
    return list->size == 0;
};

bool isCompletedLoanListFull(const CompletedLoanList* list) {
    CompletedLoanNode* test = new (nothrow) CompletedLoanNode;

    if (test == nullptr) {
        return true;
    };

    delete test;
    return false;
};

void DisplayCompletedLoansByAccount(CompletedLoanList* list, unsigned int Account_number) {
    CompletedLoanNode* node = list->head;
    while (node) {
        if (node->data.Account_number == Account_number)
            printCompletedLoan(node);
        node = node->next;
    };
};