# Bank Management System (C++ and Linked Lists)

This project is a basic **Bank Account Management System** implemented in C++. It utilizes a linked list to manage customer bank accounts, allowing users to perform various banking operations such as account creation, deposit, withdrawal, currency exchange, fund transfer, and loan application.

## Table of Contents
- [Features](#features)
- [Class Structure](#class-structure)
  - [Node Class](#node-class)
  - [Bank Class](#bank-class)
- [Functions](#functions)
  - [Public Functions](#public-functions)
- [Installation](#installation)

---

## Features

- **Account Creation**: Allows new customers to sign up by creating a bank account.
- **Account Deletion**: Removes an account from the system.
- **Currency Exchange**: Converts EGP to other currencies (USD, EUR, AED).
- **Deposit and Withdrawal**: Supports deposits to and withdrawals from an account.
- **Fund Transfer**: Facilitates money transfers between accounts.
- **Account Search**: Searches for an account by its ID.
- **Loan Application**: Checks loan eligibility based on financial criteria.

---

## Class Structure

### Node Class
The `node` class represents an individual bank account. Each `node` (or account) contains:
- **val**: A float value representing the bank account balance.
- **cash**: Current cash balance of the account.
- **name**: Name of the account holder.
- **id**: Unique identifier for the account.
- **next**: Pointer to the next node (account) in the linked list.

### Bank Class
The `bank` class manages the entire linked list of bank accounts. It includes:
- **head**: Private pointer to the first node in the linked list.
- **length**: Public integer tracking the number of accounts.

---

## Functions

### Public Functions

- **sign_up()**: Creates a new bank account.
- **displayDetails()**: Displays details of a specific account.
- **currency_exchange()**: Converts EGP to other currencies.
- **deleteAccount()**: Deletes a specified account.
- **deposite(int id)**: Deposits money into an account.
- **withdrawal(int id)**: Withdraws money from an account.
- **update()**: Updates account details.
- **search()**: Searches for an account by its ID.
- **listing()**: Lists all accounts.
- **transfer(int senderId, int receiverId, float amount)**: Transfers funds between accounts.
- **loanApplication()**: Handles the loan application process, checking eligibility based on financial criteria.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/BankAccountManagementSystem.git
   cd BankAccountManagementSystem
