
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
    employees.data = new Employee[employees.capacity];

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
            char comma;

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

            getline(ss, temp, ','); a->Account_number = stoi(temp);
            getline(ss, a->Account_type, ',');
            getline(ss, a->IBAN, ',');
            getline(ss, temp, ','); a->Branch_code = stoi(temp);
            getline(ss, a->Account_holder_name, ',');

            getline(ss, temp, ','); a->Opening_date.day = stoi(temp);
            getline(ss, temp, ','); a->Opening_date.month = stoi(temp);
            getline(ss, temp, ','); a->Opening_date.year = stoi(temp);

            getline(ss, a->Status, ',');
            getline(ss, temp, ','); a->Balance = stod(temp);

            a->transactions = createTransactionStack();
            a->dayHistory = nullptr;

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
}
void SaveAll(CustomerList *customers, const EmployeeArray &employees)
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
           << a->Balance
           << "\n";

        cn = cn->next;
    }

    fc.close();
}