#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std;
#include "utils/Date.h"

struct Employee {
    unsigned int Id;
    string Name;
    string Last_name;
    string Address;
    double salary;
    date Hire_date;
    unsigned int Bank_branch;
};

struct EmployeeArray {
    Employee* data;
    int size;
    int capacity;
};
#endif // EMPLOYEE_H
