#pragma once
#ifndef LOAN_H
#define LOAN_H	
#include <string>
using namespace std;
#include "utils/Date.h"

struct Loan {
	unsigned int ID;
	unsigned int Account_number;
	string Loan_type;        // (car, home, student, business)
	double Principal_Amount;
	double Interest_Rate;
	double Amount_Paid;
	double Remaining_Balance;
	date Start_Date;
	date End_Date;
	string Loan_Status;      // (active, completed, overdue)
};

#endif

