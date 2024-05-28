#include <iostream>
#include <string>
#include <cstdlib>
#include "includes/BankingUser.cpp"
#include <sqlite3.h>



int main()
{

	sqlite3* db;
	int rc = sqlite3_open("database.db", &db);

	char *zErrMsg = 0;
	if (rc){
		std::cout << "Error opening db";
	} else {
		std::cout << "Connection successful" << std::endl;
	}

	const char* createTableSQL = "CREATE TABLE CUSTOMERS(" 
	"ID INTEGER PRIMARY KEY AUTOINCREMENT		NOT NULL," 
	"FIRST_NAME		TEXT 	NOT NULL," 
	"LAST_NAME 		TEXT 	NOT NULL," 
	"DATE_OF_BIRTH	DATE	NOT NULL,"	
	"ADDRESS 		VARTCHAR(75)	NOT NULL," 
	"PHONE_NUMBER	VARCHAR(20)	NOT NULL," 
	"EMAIL			VARCHAR(50)	NOT NULL);";

    const char* createTableSQL2 = "CREATE TABLE ACCOUNTS("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT		NOT NULL,"
    "ACCOUNT_NUMBER INTEGER NOT NULL,"
    "BALANCE DOUBLE NOT NULL,"
    "ACCOUNT_TYPE TEXT NOT NULL,"
    "ACCOUNT_HOLDER_ID INTEGER NOT NULL,"
    "FOREIGN KEY(ACCOUNT_HOLDER_ID) REFERENCES CUSTOMERS(ID));";

	
	// std::cout << "Table has been created" << std::endl;

	// const char* insertDataSQL = "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
    //                             "VALUES (1, 'John', 'Doe', '1985-04-12', '123 Elm St, NY', 1234567890, 'johndoe@example.com'); "
    //                             "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
    //                             "VALUES (2, 'Jane', 'Smith', '1990-08-22', '456 Oak St, CA', 2345678901, 'janesmith@example.com'); "
    //                             "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
    //                             "VALUES (3, 'Bob', 'Johnson', '1975-12-30', '789 Pine St, TX', 3456789012, 'bobjohnson@example.com'); "
    //                             "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
    //                             "VALUES (4, 'Alice', 'Williams', '1988-03-15', '101 Maple St, FL', 4567890123, 'alicew@example.com'); "
    //                             "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
    //                             "VALUES (5, 'Michael', 'Brown', '1995-07-20', '202 Birch St, IL', 5678901234, 'michaelbrown@example.com');";
    //executeSQL(db, createTableSQL);


    // std::cout << "Records created successfully" << std::endl;
	executeTableSQL(db, createTableSQL2);
	// executeSQL(db, "Luis", "Abreu", "1999-25-02", "92 South 10th", "347-661-6555", "luistest@gmail.com");
	
    //executeTableSQL(db, createTableSQL);
    printTableData(db);
	//sqlite3_close(db);

	Bank b;
	b.checkUserMembership();

    std::cout << "Welcome to the bank" << std::endl;
}
