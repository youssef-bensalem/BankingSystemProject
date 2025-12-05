#ifndef TRANSACTIONSTACK_H	
#define TRANSACTIONSTACK_H	
#include "Transaction.h"

Transaction createTransaction(
	unsigned int transactionID,
	unsigned int accountNumber,
	const string& type,
	double amount,
	const date& d
);

StackNode* createTransactionNode(const Transaction& t);

void deleteTransaction(Transaction* transaction);

TransactionStack* createTransactionStack();

void deleteTransactionStack(TransactionStack* stack);

int pushTransaction(TransactionStack& stack, Transaction* transaction);

Transaction* popTransaction(TransactionStack& stack);

Transaction* peekTransaction(const TransactionStack& stack);

void clearTransactionStack(TransactionStack& stack);

bool isTransactionStackEmpty(const TransactionStack& stack);

bool isTransactionStackFull(const TransactionStack& stack);

void displayTransactionStack(const TransactionStack& stack);

int transactionStackSize(const TransactionStack& stack);
#endif 
