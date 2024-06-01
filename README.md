# Bank Account Balance Checker

This project is a simple command-line program written in C++ that connects to a SQLite3 database and retrieves the balance of a bank account based on the email address provided by the user. The program demonstrates basic database operations, user input handling, and password hashing using the libsodium library.

## Features

- Connects to a SQLite3 database
- Retrieves the account balance for a given email address
- Hashes passwords using libsodium
- Command-line interface for easy usage

## Prerequisites

Before you can build and run this project, ensure you have the following installed on your system:

- [SQLite3](https://www.sqlite.org/download.html)
- [libsodium](https://libsodium.gitbook.io/doc/installation)
- [g++](https://gcc.gnu.org/install/index.html) or any other C++ compiler

## Setup

1. **Clone the repository:**

    ```bash
    git clone https://github.com/splicid/bank-account-balance-checker.git
    cd bank-account-balance-checker
    ```

2. **Create the SQLite database and tables:**

    You need to create a SQLite database named `bank.db` and the necessary tables. You can do this using the SQLite command-line tool:

    ```sql
    sqlite3 bank.db

    CREATE TABLE CUSTOMERS (
        CUSTOMER_ID INTEGER PRIMARY KEY AUTOINCREMENT,
        FIRST_NAME TEXT NOT NULL,
        LAST_NAME TEXT NOT NULL,
        ADDRESS TEXT NOT NULL,
        PHONE_NUMBER TEXT NOT NULL
    );

    CREATE TABLE ACCOUNTS (
        ACCOUNT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
        CUSTOMER_ID INTEGER,
        ACCOUNT_EMAIL TEXT NOT NULL,
        ACCOUNT_PASSWORD TEXT NOT NULL,
        BALANCE REAL NOT NULL,
        FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMERS (CUSTOMER_ID)
    );

    INSERT INTO ACCOUNTS (CUSTOMER_ID, ACCOUNT_EMAIL, ACCOUNT_PASSWORD, BALANCE) VALUES (1, 'test@gmail.com', 'hashedpassword', 1000.0);
    ```

    Replace `'hashedpassword'` with an actual hashed password if necessary.

3. **Compile the program:**

    ```bash
    g++ -o check_balance check_balance.cpp -lsqlite3 -lsodium
    ```

## Usage

To check the balance of an account, run the program from the command line and provide the email address as an argument:

```bash
./check_balance test@gmail.com
