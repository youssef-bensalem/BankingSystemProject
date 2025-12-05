#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
#include "Loan.h"
#include "Transaction.h"
#include "Date.h"

struct Account {
	unsigned int Account_number;// unique
	string Account_type;
	string IBAN;
	unsigned int Branch_code;
	string Account_holder_name;
	date Opening_date;
	string Status; //(active, inactive, closed)
	double Balance; //(in Tunisian dinars)

	LoanList loans;
	TransactionStack* transactions; // Stack of transactions
};

#endif
