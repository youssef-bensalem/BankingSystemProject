#include "utils/DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "core/LoanListMeth.h"
#include "core/CompletedLoanListMeth.h"
#include "core/ArchivedAccount.h"
#include "core/Loan.h"
#include "core/LoanNode.h"

using namespace std;

static Loan parseLoan(const string& line) {
    Loan L;
    string temp;
    stringstream ss(line);

    getline(ss, temp, ','); L.ID = (unsigned int)stoul(temp);
    getline(ss, temp, ','); L.Account_number = (unsigned int)stoul(temp);
    getline(ss, L.Loan_type, ',');
    getline(ss, temp, ','); L.Principal_Amount = stod(temp);
    getline(ss, temp, ','); L.Interest_Rate = stod(temp);
    getline(ss, temp, ','); L.Amount_Paid = stod(temp);
    getline(ss, temp, ','); L.Remaining_Balance = stod(temp);

    getline(ss, temp, ','); L.Start_Date.day = stoi(temp);
    getline(ss, temp, ','); L.Start_Date.month = stoi(temp);
    getline(ss, temp, ','); L.Start_Date.year = stoi(temp);

    getline(ss, temp, ','); L.End_Date.day = stoi(temp);
    getline(ss, temp, ','); L.End_Date.month = stoi(temp);
    getline(ss, temp, ','); L.End_Date.year = stoi(temp);

    getline(ss, L.Loan_Status, ',');

    return L;
}

static string serializeLoan(const Loan& L) {
    stringstream s;
    s << L.ID << ","
      << L.Account_number << ","
      << L.Loan_type << ","
      << L.Principal_Amount << ","
      << L.Interest_Rate << ","
      << L.Amount_Paid << ","
      << L.Remaining_Balance << ","
      << L.Start_Date.day << ","
      << L.Start_Date.month << ","
      << L.Start_Date.year << ","
      << L.End_Date.day << ","
      << L.End_Date.month << ","
      << L.End_Date.year << ","
      << L.Loan_Status;
    return s.str();
}

static ArchivedAccount parseArchived(const string& line) {
    ArchivedAccount A;
    A.acc = new Account();

    string temp;
    stringstream ss(line);

    getline(ss, temp, ','); A.acc->Account_number = (unsigned int)stoul(temp);
    getline(ss, A.acc->Account_type, ',');
    getline(ss, A.acc->IBAN, ',');
    getline(ss, temp, ','); A.acc->Branch_code = (unsigned int)stoul(temp);
    getline(ss, A.acc->Account_holder_name, ',');

    getline(ss, temp, ','); A.acc->Opening_date.day = stoi(temp);
    getline(ss, temp, ','); A.acc->Opening_date.month = stoi(temp);
    getline(ss, temp, ','); A.acc->Opening_date.year = stoi(temp);

    getline(ss, A.acc->Status, ',');

    getline(ss, temp, ','); A.acc->Balance = stod(temp);

    A.acc->transactions = createTransactionStack();
    A.acc->dayHistory = nullptr;
    A.acc->loans = createLoanList();

    return A;
}

static string serializeArchived(const ArchivedAccount& A) {
    const Account* acc = A.acc;
    stringstream s;
    s << acc->Account_number << ","
      << acc->Account_type << ","
      << acc->IBAN << ","
      << acc->Branch_code << ","
      << acc->Account_holder_name << ","
      << acc->Opening_date.day << ","
      << acc->Opening_date.month << ","
      << acc->Opening_date.year << ","
      << acc->Status << ","
      << acc->Balance;
    return s.str();
}

void LoadAll(CustomerList *&customers, EmployeeArray &employees, ArchivedAccountArray &archived, CompletedLoanList *&completedList)
{
    createCustomerList(customers);

    employees.size = 0;
    employees.capacity = 10;
    employees.data = new Employee[employees.capacity];

    archived.size = 0;
    if (archived.capacity == 0) archived.capacity = 5;
    if (!archived.data) archived.data = new ArchivedAccount[archived.capacity];

    if (!completedList) completedList = createCompletedLoanList();

    ifstream fe("data/employees.txt");
    if (fe.is_open())
    {
        string line;
        while (getline(fe, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string temp;
            Employee e;

            getline(ss, temp, ','); e.Id = stoi(temp);
            getline(ss, e.Name, ',');
            getline(ss, e.Last_name, ',');
            getline(ss, e.Address, ',');
            getline(ss, temp, ','); e.salary = stod(temp);
            getline(ss, temp, ','); e.Hire_date.day = stoi(temp);
            getline(ss, temp, ','); e.Hire_date.month = stoi(temp);
            getline(ss, temp, ','); e.Hire_date.year = stoi(temp);
            getline(ss, temp, ','); e.Bank_branch = stoi(temp);

            if (employees.size == employees.capacity)
            {
                employees.capacity *= 2;
                Employee *newArr = new Employee[employees.capacity];
                for (int i = 0; i < employees.size; i++)
                    newArr[i] = employees.data[i];
                delete[] employees.data;
                employees.data = newArr;
            }

            employees.data[employees.size++] = e;
        }
        fe.close();
    }
    ifstream fc("data/customers.txt");
    if (fc.is_open())
    {
        string line;

        while (getline(fc, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string temp;

            Customer *c = new Customer();
            Account  *a = new Account();

            getline(ss, c->loginUsername, ',');
            getline(ss, c->loginPassword, ',');

            getline(ss, temp, ','); a->Account_number = (unsigned int)stoul(temp);
            getline(ss, a->Account_type, ',');
            getline(ss, a->IBAN, ',');
            getline(ss, temp, ','); a->Branch_code = (unsigned int)stoul(temp);
            getline(ss, a->Account_holder_name, ',');

            getline(ss, temp, ','); a->Opening_date.day = stoi(temp);
            getline(ss, temp, ','); a->Opening_date.month = stoi(temp);
            getline(ss, temp, ','); a->Opening_date.year = stoi(temp);

            getline(ss, a->Status, ',');
            getline(ss, temp, ','); a->Balance = stod(temp);

            a->transactions = createTransactionStack();
            a->dayHistory = nullptr;
            a->loans = createLoanList();

            c->account = a;

            CustomerNode *node = new CustomerNode{c, nullptr};

            if (!customers->head)
                customers->head = node;
            else
            {
                CustomerNode *p = customers->head;
                while (p->next)
                    p = p->next;
                p->next = node;
            }
        }

        fc.close();
    }

    ifstream fa("data/archived_accounts.txt");
    if (fa.is_open()) {
        string line;
        while (getline(fa, line)) {
            if (line.empty()) continue;
            ArchivedAccount A = parseArchived(line);
            if (archived.size == archived.capacity) {
                int newCap = archived.capacity * 2;
                ArchivedAccount* newData = new ArchivedAccount[newCap];
                for (int i = 0; i < archived.size; ++i) newData[i] = archived.data[i];
                delete[] archived.data;
                archived.data = newData;
                archived.capacity = newCap;
            }
            archived.data[archived.size++] = A;
        }
        fa.close();
    }

    ifstream fl("data/loans.txt");
    if (fl.is_open()) {
        string line;
        while (getline(fl, line)) {
            if (line.empty()) continue;
            Loan L = parseLoan(line);

            CustomerNode* cn = customers->head;
            while (cn) {
                if (cn->data->account && cn->data->account->Account_number == L.Account_number) {
                    if (!cn->data->account->loans) cn->data->account->loans = createLoanList();
                    insertLoan(cn->data->account->loans, L);
                    break;
                }
                cn = cn->next;
            }
        }
        fl.close();
    }

    ifstream fcl("data/completed_loans.txt");
    if (fcl.is_open()) {
        string line;
        while (getline(fcl, line)) {
            if (line.empty()) continue;
            Loan L = parseLoan(line);
            addCompletedLoan(*completedList, L);
        }
        fcl.close();
    }
}

void SaveAll(CustomerList *customers, const EmployeeArray &employees, const ArchivedAccountArray &archived, const CompletedLoanList *completedList)
{
    ofstream fe("data/employees.txt");
    for (int i = 0; i < employees.size; i++)
    {
        const Employee &e = employees.data[i];
        fe << e.Id << ","
           << e.Name << ","
           << e.Last_name << ","
           << e.Address << ","
           << e.salary << ","
           << e.Hire_date.day << ","
           << e.Hire_date.month << ","
           << e.Hire_date.year << ","
           << e.Bank_branch
           << "\n";
    }
    fe.close();

    ofstream fc("data/customers.txt");
    CustomerNode *cn = customers->head;

    while (cn)
    {
        Customer *c = cn->data;
        Account *a = c->account;
        fc << c->loginUsername << ","
           << c->loginPassword << ","
           << a->Account_number << ","
           << a->Account_type << ","
           << a->IBAN << ","
           << a->Branch_code << ","
           << a->Account_holder_name << ","
           << a->Opening_date.day << ","
           << a->Opening_date.month << ","
           << a->Opening_date.year << ","
           << a->Status << ","
           << a->Balance << "\n";
        cn = cn->next;
    }
    fc.close();

    ofstream fa("data/archived_accounts.txt");
    for (int i = 0; i < archived.size; ++i) {
        fa << serializeArchived(archived.data[i]) << "\n";
    }
    fa.close();

    ofstream fl("data/loans.txt");
    CustomerNode* cur = customers->head;
    while (cur) {
        Account* a = cur->data->account;
        if (a && a->loans) {
            LoanNode* ln = a->loans->head;
            while (ln) {
                fl << serializeLoan(ln->data) << "\n";
                ln = ln->next;
            }
        }
        cur = cur->next;
    }
    fl.close();
    
    ofstream fcl("data/completed_loans.txt");
    if (completedList) {
        CompletedLoanNode* node = completedList->head;
        while (node) {
            fcl << serializeLoan(node->data) << "\n";
            node = node->next;
        }
    }
    fcl.close();
}
