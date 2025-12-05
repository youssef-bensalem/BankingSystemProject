#include <iostream>
#include "LoanRequestQueueMeth.h"
using namespace std;

LoanRequestQueue* createLoanRequestQueue() {
    LoanRequestQueue* queue = new (nothrow) LoanRequestQueue();
    if (!queue) {
        cerr << "Memory allocation failed for LoanRequestQueue." << endl;
        return nullptr;
    }
    else {
        queue->front = nullptr;
        queue->tail = nullptr;
    }
    return queue;
}

void destroyLoanRequestQueue(LoanRequestQueue* queue) {
    LoanRequestNode* current = queue->front;
    while (current != nullptr) {
        queue->front = current->next;
        delete current;
        current = queue->front;
    }
    delete queue;
}

LoanRequestNode* createLoanRequestNode(const LoanRequest& request) {
    LoanRequestNode* newNode = new (nothrow) LoanRequestNode();
    if (!newNode) {
        cerr << "Memory allocation failed for LoanRequestNode." << endl;
        return nullptr;
    }
    newNode->data = request;
    return newNode;
}

int enqueueLoanRequest(LoanRequestQueue* queue, const LoanRequest& request) {
    if (LoanRequestQueueFull(*queue)) {
        cout << "Loan Request Queue is full. Cannot enqueue new request." << endl;
        return 0;
    }

    LoanRequestNode* newNode = createLoanRequestNode(request);

    if (LoanRequestQueueEmpty(*queue)) {
        queue->front = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    return 1;
}

LoanRequest dequeueLoanRequest(LoanRequestQueue* queue) {
    LoanRequest request;
    if (LoanRequestQueueEmpty(*queue)) {
        cout << "Loan Request Queue is empty. Cannot dequeue request." << endl;
        return request;
    }
    else {
        LoanRequestNode* temp = queue->front;
        request = temp->data;
        queue->front = temp->next;
        if (queue->front == nullptr) {
            queue->tail = nullptr;
        }
        delete temp;
        return request;
    }
}

bool LoanRequestQueueEmpty(const LoanRequestQueue& queue) {
    return (queue.front == nullptr);
}

bool LoanRequestQueueFull(const LoanRequestQueue& queue) {
    LoanRequestNode* temp = new (nothrow) LoanRequestNode();
    if (temp == nullptr) {
        return true;
    }
    delete temp;
    return false;
}

int getLoanRequestQueueSize(const LoanRequestQueue* queue) {
    int size = 0;
    LoanRequestNode* current = queue->front;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

void printLoanRequest(const LoanRequest& request) {
    cout << "Request ID: " << request.requestID << endl;
    cout << "Account Number: " << request.accountNumber << endl;
    cout << "Loan Type: " << request.loanType << endl;
    cout << "Requested Amount: " << request.requestedAmount << endl;
    cout << "Interest Rate: " << request.interestRate << endl;
    cout << "Duration (Months): " << request.durationMonths << endl;
    cout << "Request Date: " << request.requestDate.day << "/" 
         << request.requestDate.month << "/" 
         << request.requestDate.year << endl;
    cout << "Status: " << request.status << endl;
}

void printAllLoanRequests(const LoanRequestQueue& queue) {
    if (LoanRequestQueueEmpty(queue)) {
        cout << "Loan Request Queue is empty." << endl;
        return;
    }
    LoanRequestNode* current = queue.front;
    while (current != nullptr) {
        printLoanRequest(current->data);
        cout << "------------------------" << endl;
        current = current->next;
    }
}
