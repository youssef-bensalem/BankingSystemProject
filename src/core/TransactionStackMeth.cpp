#include "core/Transaction.h"
#include "core/TransactionStackMeth.h"
#include <iostream>
using namespace std;

static unsigned int nextTransactionID = 1; // Static variable to keep track of the next unique Transaction ID
Transaction createTransaction(
	unsigned int accountNumber,
	const string& type,
	double amount,
	const date& d
) {
	Transaction t;

	t.Transaction_ID = nextTransactionID++;   // ✔ Unique ID
	t.Account_Number = accountNumber;
	t.Type = type;
	t.Amount = amount;
	t.Date = d;

	return t;
}

StackNode* createTransactionNode(const Transaction& t) {
	StackNode* newNode = new (nothrow) StackNode();
	if (!newNode) {
		cerr << "Memory allocation failed for Transaction Node.\n";
		return nullptr;
	}
	newNode->transaction = t;
	newNode->next = nullptr;
	return newNode;
}

void deleteTransaction(StackNode* transaction)
{
	delete transaction;
}

TransactionStack* createTransactionStack()
{
	TransactionStack* stack = new (nothrow) TransactionStack {
		nullptr
	};

	if (stack == nullptr)
	{
		cout << "Memory allocation failed for Transaction Stack." << endl;
		return nullptr;
	}

	stack->top = nullptr;
	return stack;
}

void deleteTransactionStack(TransactionStack *stack)
{
	StackNode *t = stack->top;
	while (t != nullptr)
	{
		stack->top = t->next;
		deleteTransaction(t);
		t = stack->top;
	}
	delete stack;
}

int pushTransaction(TransactionStack *stack, StackNode *transaction)
{
	int success = 1;
	if (isTransactionStackFull(stack))
	{
		cout << "Transaction Stack is full. Cannot push new transaction." << endl;
		success = 0;
	}
	else
	{
		transaction->next = stack->top;
		stack->top = transaction;
	}
	return success;
}

StackNode *popTransaction(TransactionStack* stack)
{
	if (isTransactionStackEmpty(stack))
	{
		cout << "\nTransaction stack is empty";
	}

	StackNode *popped = stack->top;
	stack->top = stack->top->next;

	return popped;
}

StackNode *peekTransaction(const TransactionStack* stack)
{
	if (stack->top == nullptr)
	{
		cout << "Stack is empty" << endl;
	}
	return stack->top;
}

void clearTransactionStack(TransactionStack* stack)
{
	StackNode *current = stack->top;
	while (current != nullptr)
	{
		StackNode *temp = current;
		current = current->next;
		delete temp;
	}
	stack->top = nullptr;
}

bool isTransactionStackEmpty(const TransactionStack* stack)
{
	return (stack->top == nullptr);
}

bool isTransactionStackFull(const TransactionStack* stack)
{
	StackNode *temp = new (nothrow) StackNode;
	if (!temp)
		return true;
	delete temp;
	return false;
}

void DisplayTransactionStack(const TransactionStack* stack)
{
	StackNode* t = stack->top;

	if (!t)
	{
		cout << "Transaction Stack is empty." << endl;
		return;
	}

	while (t != nullptr)
	{
		//cout << t->Transaction_ID << " " << t->Amount << " " << t->Date-> << endl;
		t = t->next;
	}
}

int transactionStackSize(const TransactionStack* stack)
{
	int size = 0;
	StackNode *t = stack->top;

	while (t != nullptr)
	{
		size++;
		t = t->next;
	}

	return size;
}
