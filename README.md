# Banking Management System – Data Structures Project

## 1. Overview
This project implements a complete Banking Management System in C++, applying arrays, stacks, queues, singly and doubly linked lists to manage customers, employees, accounts, loans, and financial transactions.

The application simulates key operations of a real bank while meeting the official project specifications. All source files and this report are included in the project’s submission package.

## 2. System Architecture
The system provides two interfaces:
- Customer Interface
- Employee Interface

All data structures load from files at startup and are initialized with default values.

## 3. Data Structures

### Accounts
Each customer owns one account storing:
- Account number (unique)
- Type
- IBAN
- Branch code
- Holder name
- Opening date
- Status (active, inactive, closed)
- Balance

Each account also maintains:
- A doubly linked list of loans
- A stack of daily transactions

### Loans (Doubly Linked List)
Each loan stores:
- Loan ID
- Type (car, home, student, business)
- Principal, interest rate
- Amount paid, remaining balance
- Start date, end date
- Status (active, completed, overdue)

### Completed Loans (Singly Linked List)
Completed loans are transferred here.

### Daily Transactions (Stack)
Each transaction contains:
- Transaction ID
- Account number
- Type (deposit/withdrawal)
- Amount
- Date

Withdrawals follow allowed denominations: 10, 20, 50 TND.

At end of day, all stack entries are copied to a singly linked list for permanent history.

### Employees (Array)
Each employee includes:
- ID
- First/last name
- Address
- Salary
- Hire date
- Branch code

### Archived Accounts (Array)
Closed accounts are moved to an archived list.

### Loan Requests (Queue)
Processed in FIFO order:
- Accepted → added to customer's loan list
- Declined → permanently removed

## 4. Customer Features
- Secure login
- View all loans
- Submit loan request
- Withdraw money (10/20/50 TND)
- Deposit money
- View same-day transactions
- Undo last transaction

## 5. Employee Features

### Employee Management
- Add, delete, edit employee
- Display employees alphabetically
- Display employees by branch
- Show earliest and latest hired employees

### Accounts
- Add customer account
- Display accounts
- Change account status
- Archive closed accounts

### Loans
- View customer's loans
- Modify loan status
- Move completed loans to singly linked list
- Process loan requests FIFO

### Daily Operations
- Manage transaction stacks
- Finalize day logs

## 6. Statistics Module
- Total loans
- Loans by type
- Loans by status
- Active loans between chosen dates
- Customer with most loans
- Customer with highest balance
- Customer with lowest balance
- Total employees
- Employees per branch

## 7. File Handling
At startup:
- Load all structures from text files
- Ensure consistent updates
- Autosave changes

## 8. Conclusion
This project demonstrates practical data structure usage in a banking environment, covering authentication, account management, loan processing, employee operations, statistics, and transaction logging.
