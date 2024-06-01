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
	const char* customerTable = "CREATE TABLE IF NOT EXISTS CUSTOMERS ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"FIRST_NAME TEXT NOT NULL, "
		"LAST_NAME TEXT NOT NULL, "
		"ADDRESS TEXT NOT NULL, "
		"PHONE_NUMBER TEXT NOT NULL);";

	const char* accountTable = "CREATE TABLE IF NOT EXISTS ACCOUNTS ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"CUSTOMER_ID INTEGER NOT NULL, "
		"ACCOUNT_EMAIL TEXT NOT NULL UNIQUE, "
		"ACCOUNT_PASSWORD TEXT NOT NULL, "
		"BALANCE REAL NOT NULL,"
		"FOREIGN KEY(CUSTOMER_ID) REFERENCES CUSTOMERS(ID));";

	// Create the tables
	try
	{
		/* code */
		executeTableSQL(db, customerTable);
		executeTableSQL(db, accountTable);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	if (rc){
		std::cout << "Error opening db";
	} else {
		std::cout << "Connection successful" << std::endl;
	}

	Bank b;
	b.checkUserMembership(db);
	sqlite3_close(db);

}
