
#pragma once
#include "core/Customer.h"
#include "core/Employee.h"
#include "core/Account.h"
#include <string>

namespace DataManager {
    void LoadAll(CustomerList*& customers, EmployeeArray& employees);
    void SaveAll(CustomerList* customers, const EmployeeArray& employees);
}
