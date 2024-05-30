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

        const char* createCustomerTableSQL = R"(
            CREATE TABLE IF NOT EXISTS CUSTOMERS (
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                FIRST_NAME TEXT NOT NULL,
                LAST_NAME TEXT NOT NULL,
                ADDRESS TEXT NOT NULL,
                PHONE_NUMBER TEXT NOT NULL
            );
        )";

        const char* createAccountTableSQL = R"(
            CREATE TABLE IF NOT EXISTS ACCOUNTS (
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                CUSTOMER_ID INTEGER NOT NULL,
                ACCOUNT_EMAIL TEXT NOT NULL,
                ACCOUNT_PASSWORD TEXT NOT NULL,
                FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMERS(ID)
            );
        )";


		// executeTableSQL(db, createCustomerTableSQL);
		// executeTableSQL(db, createAccountTableSQL);
		std::string firstName = "John";
		std::string lastName = "Doe";
		std::string address = "1234 Elm St";
		std::string phoneNumber = "123-456-7890";

		// executeCustomerSQL(db, firstName.c_str(), lastName.c_str(), address.c_str(), phoneNumber.c_str());

	std::string accountEmail = "test@gmail.com";
	std::string accountPassword = "password";

	// executeCustomerSQL(db, firstName, lastName, address, phoneNumber);
	// executeAccountSQL(db, 1, accountEmail, accountPassword);

    // printTableData(db);
	//sqlite3_close(db);

	Bank b;
	b.testingInsert();

    //std::cout << "Welcome to the bank" << std::endl;

}
