#ifndef TRANSACTIONSTACK_H	
#define TRANSACTIONSTACK_H	

#include "core/Transaction.h"
#include "core/TransactionStackMeth.h"
#include <iostream>
using namespace std;

Transaction createTransaction(
	unsigned int accountNumber,
	const string& type,
	double amount,
	const date& d
);
StackNode* createTransactionNode(const Transaction& t);
void deleteTransaction(StackNode* transaction);
TransactionStack* createTransactionStack();
void deleteTransactionStack(TransactionStack *stack);
int pushTransaction(TransactionStack *stack, StackNode *transaction);
StackNode *popTransaction(TransactionStack* stack);
StackNode *peekTransaction(const TransactionStack* stack);
void clearTransactionStack(TransactionStack* stack);
bool isTransactionStackEmpty(const TransactionStack* stack);
bool isTransactionStackFull(const TransactionStack* stack);
void DisplayTransactionStack(const TransactionStack* stack);
int transactionStackSize(const TransactionStack* stack);

#endif 
