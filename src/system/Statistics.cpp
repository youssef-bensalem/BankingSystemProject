#include <iostream>
#include "system/Statistics.h"

using namespace std;

int TotalNumberOfLoans(CustomerList* customers) {
    if (customers->head == nullptr) {
        cout << "No accounts to display.\n";
        return 0;
    }
    int numberOfLoans = 0;
    CustomerNode* current1 = customers->head;
    while (current1) {
        LoanNode* current2 = current1->data->account->loans->head;
        while (current2) {
            numberOfLoans++;
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return numberOfLoans;
}

int CountLoansByType(CustomerList* customers, const string& type) {
    if (customers->head == nullptr) {
        cout << "No accounts to display.\n";
        return 0;
    }
    int CarType = 0;
    int HomeType = 0;
    int StudentType = 0;
    int BusinessType = 0;
    CustomerNode* current1 = customers->head;
    while (current1) {
        LoanNode* current2 = current1->data->account->loans->head;
        while (current2) {
            if (current2->data.Loan_type == "car" || current2->data.Loan_type == "Car") CarType++;
            if (current2->data.Loan_type == "home" || current2->data.Loan_type == "Home") HomeType++;
            if (current2->data.Loan_type == "student" || current2->data.Loan_type == "Student") StudentType++;
            if (current2->data.Loan_type == "business" || current2->data.Loan_type == "Business") BusinessType++;
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    if (type == "car" || type == "Car") return CarType;
    if (type == "home" || type == "Home") return HomeType;
    if (type == "student" || type == "Student") return StudentType;
    if (type == "business" || type == "Business") return BusinessType;

    cout << "Invalid loan type: " << type << endl;
    return 0;
}

int CountLoansByStatus(CustomerList* customers, const string& status) {
    if (customers->head == nullptr) {
        cout << "No accounts to display.\n";
        return 0;
    }
    int Active = 0;
    int Completed = 0;
    int Overdue = 0;
    CustomerNode* current1 = customers->head;
    while (current1) {
        LoanNode* ln = current1->data->account->loans->head;
        while (ln) {
            string s = ln->data.Loan_Status;

            if (s == "active" || s == "Active") Active++;
            if (s == "completed" || s == "Completed") Completed++;
            if (s == "overdue" || s == "Overdue") Overdue++;

            ln = ln->next;
        }

        current1 = current1->next;
    }
    if (status == "active" || status == "Active") return Active;
    if (status == "completed" || status == "Completed") return Completed;
    if (status == "overdue" || status == "Overdue") return Overdue;

    cout << "Invalid loan status: " << status << endl;
    return 0;
}

int compareDates(const date& a, const date& b) {
    if (a.year < b.year) return -1;
    if (a.year > b.year) return 1;

    // years equal → compare months
    if (a.month < b.month) return -1;
    if (a.month > b.month) return 1;

    // months equal → compare days
    if (a.day < b.day) return -1;
    if (a.day > b.day) return 1;

    // exactly the same date
    return 0;
}   //used in activeLoansInRange

int ActiveLoansInRange(CustomerList* customers, const date& startD, const date& endD) {
    if (customers->head == nullptr) {
        cout << "No customers available.\n";
        return 0;
    }
    int countLoans = 0;
    CustomerNode* current1 = customers->head;
    while (current1) {
        LoanNode* current2 = current1->data->account->loans->head;
        while (current2) {
            Loan& L = current2->data;
            if (L.Loan_Status == "active" || L.Loan_Status == "Active") {
                bool startsBeforeRangeEnds =compareDates(L.Start_Date, endD) <= 0;
                bool endsAfterRangeStarts =compareDates(L.End_Date, startD) >= 0;
                // If loan overlaps the user range
                if (startsBeforeRangeEnds && endsAfterRangeStarts) countLoans++;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return countLoans;
}

Customer* CustomerWithMostLoans(CustomerList* customers) {
    if (customers->head == nullptr) {
        cout << "No customers available.\n";
        return nullptr;
    }
    CustomerNode* current = customers->head;
    Customer* highestCustomer = nullptr;
    int maxLoans = 0;

    while (current) {
        int loanCount = current->data->account->loans->size;

        if (loanCount > maxLoans) {
            maxLoans = loanCount;
            highestCustomer = current->data;
        }

        current = current->next;
    }

    return highestCustomer;
}

Customer* CustomerWithHighestBalance(CustomerList* customers) {
    if (customers->head == nullptr) {
        cout << "No customers available.\n";
        return nullptr;
    }
    CustomerNode* current = customers->head;
    Customer* richest = current->data;
    current = current->next;

    while (current) {
        if (current->data->account->Balance > richest->account->Balance) {
            richest = current->data;
        }
        current = current->next;
    }
    return richest; //needs display 
}

Customer* CustomerWithLowestBalance(CustomerList* customers) {
    if (customers->head == nullptr) {
        cout << "No customers available.\n";
        return nullptr;
    }
    CustomerNode* current = customers->head;
    Customer* poorest = current->data;
    current = current->next;

    while (current) {
        if (current->data->account->Balance < poorest->account->Balance) {
            poorest = current->data;
        }
        current = current->next;
    }
    return poorest;
}

int TotalEmployees(const EmployeeArray& employees) {
    return employees.size;
}
    
int EmployeesPerBranch(const EmployeeArray& employees, unsigned int branchCode) {
    int count = 0;
    for (int i = 0; i < employees.size; i++) {
        if (employees.data[i].Bank_branch == branchCode) {
            count++;
        }
    }
    return count;
}




