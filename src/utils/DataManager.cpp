
#include "utils/DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void LoadAll(CustomerList *&customers, EmployeeArray &employees)
{
    createCustomerList(customers);
    employees.size = 0;
    employees.capacity = 10;
    employees.data = new Employee[10];

    // load employees
    ifstream fe("data/employees.txt");
    if (fe.is_open())
    {
        string line;
        while (getline(fe, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            Employee e;
            char comma;
            ss >> e.Id >> comma;
            getline(ss, e.Name, ',');
            getline(ss, e.Last_name, ',');
            getline(ss, e.Address, ',');
            ss >> e.salary >> comma;
            ss >> e.Hire_date.day >> comma >> e.Hire_date.month >> comma >> e.Hire_date.year >> comma;
            ss >> e.Bank_branch;
            employees.data[employees.size++] = e;
        }
    }

    // load customers + accounts
    ifstream fc("data/customers.txt");
    if (fc.is_open())
    {
        string line;
        while (getline(fc, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            Customer *c = new Customer();
            getline(ss, c->loginUsername, ',');
            getline(ss, c->loginPassword, ',');

            Account *acc = new Account();
            ss >> acc->Account_number;
            ss.ignore();
            getline(ss, acc->Account_type, ',');
            getline(ss, acc->IBAN, ',');
            ss >> acc->Branch_code;
            ss.ignore();
            getline(ss, acc->Account_holder_name, ',');
            ss >> acc->Opening_date.day;
            ss.ignore();
            ss >> acc->Opening_date.month;
            ss.ignore();
            ss >> acc->Opening_date.year;
            ss.ignore();
            getline(ss, acc->Status, ',');
            ss >> acc->Balance;

            acc->transactions = createTransactionStack();
            acc->dayHistory = nullptr;

            c->account = acc;

            CustomerNode *node = new CustomerNode{c, customers->head};
            customers->head = node;
        }
    }
}
void SaveAll(CustomerList *customers, const EmployeeArray &employees)
{
    ofstream fe("data/employees.txt");
    for (int i = 0; i < employees.size; i++)
    {
        Employee e = employees.data[i];
        fe << e.Id << "," << e.Name << "," << e.Last_name << "," << e.Address << "," << e.salary << "," << e.Hire_date.day << "," << e.Hire_date.month << "," << e.Hire_date.year << "," << e.Bank_branch << "\n";
    }
    fe.close();
    ofstream fc("data/customers.txt");
    CustomerNode *cn = customers->head;
    while (cn)
    {
        Customer *c = cn->data;
        Account *a = c->account;
        fc << c->loginUsername << "," << c->loginPassword << "," << a->Account_number << "," << a->Account_type << "," << a->IBAN << "," << a->Branch_code << "," << a->Account_holder_name << "," << a->Opening_date.day << "," << a->Opening_date.month << "," << a->Opening_date.year << "," << a->Status << "," << a->Balance << "\n";
        cn = cn->next;
    }
    fc.close();
}
