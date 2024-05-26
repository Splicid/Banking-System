#include <iostream>
#include <string>
#include <sqlite3.h>


class Bank
{
private:
	std::string m_accountHolderName;
	double m_customerBalance;
	int m_accountNumber;

public:

	void customerBalance()
	{
		std::cout << "Your currently have: " << m_accountHolderName << std::endl;
	}

	Bank()
	{
		m_accountHolderName = "";
		m_customerBalance = 0;
		m_accountNumber = 1;
	}

	int checkUserMembership()
	{
		std::string answer;
		std::cout << "Do you have an account. yes/no: ";
		std::cin >> answer;
		if (answer == "yes")
		{
			return true;
		}
		else {
			newUser();
		}
		return 0;
	}

	std::string newUser()
	{
		std::cout << "Enter your full name: ";
		std::cin.ignore();
		std::getline(std::cin, m_accountHolderName);
		std::cout << m_accountHolderName << std::endl;
		return m_accountHolderName;
	}

	int accountActionable()
	{
		return 0;
	}
};

class AccountCreation
{
private:
	std::string m_accountHolderName;
	double m_customerID; 
	int m_accountNumber;

public:
	std::string newUser()
	{
		std::cout << "Enter your full name";
		std::cin >> m_accountHolderName;
		return m_accountHolderName;
	}
	
};

int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void executeSQL(sqlite3* db, const char* sql)
{
	char* errorMessage = 0;
	int rc = sqlite3_exec(db, sql, 0, 0, &errorMessage);
	if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

void printTableData(sqlite3* db) {
    const char* querySQL = "SELECT * FROM CUSTOMERS";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, querySQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "ID | FIRST_NAME | LAST_NAME | DATE_OF_BIRTH | ADDRESS | PHONE_NUMBER | EMAIL" << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << sqlite3_column_int(stmt, 0) << " | "
                  << sqlite3_column_text(stmt, 1) << " | "
                  << sqlite3_column_text(stmt, 2) << " | "
                  << sqlite3_column_text(stmt, 3) << " | "
                  << sqlite3_column_text(stmt, 4) << " | "
                  << sqlite3_column_int(stmt, 5) << " | "
                  << sqlite3_column_text(stmt, 6) << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main()
{
	// Bank bank;
	// bank.checkUserMembership();
	sqlite3* db;
	int rc = sqlite3_open("database.db", &db);

	char *zErrMsg = 0;
	if (rc){
		std::cout << "Error opening db";
	} else {
		std::cout << "Connection successful" << std::endl;
	}

	const char* createTableSQL = "CREATE TABLE CUSTOMERS(" 
	"ID INT PRIMARY KEY		NOT NULL," 
	"FIRST_NAME		TEXT 	NOT NULL," 
	"LAST_NAME 		TEXT 	NOT NULL," 
	"DATE_OF_BIRTH	DATE	NOT NULL,"	
	"ADDRESS 		TEXT	NOT NULL," 
	"PHONE_NUMBER	INT		NOT NULL," 
	"EMAIL			TEXT	NOT NULL);";

	executeSQL(db, createTableSQL);
	std::cout << "Table has been created" << std::endl;

	const char* insertDataSQL = "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
                                "VALUES (1, 'John', 'Doe', '1985-04-12', '123 Elm St, NY', 1234567890, 'johndoe@example.com'); "
                                "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
                                "VALUES (2, 'Jane', 'Smith', '1990-08-22', '456 Oak St, CA', 2345678901, 'janesmith@example.com'); "
                                "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
                                "VALUES (3, 'Bob', 'Johnson', '1975-12-30', '789 Pine St, TX', 3456789012, 'bobjohnson@example.com'); "
                                "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
                                "VALUES (4, 'Alice', 'Williams', '1988-03-15', '101 Maple St, FL', 4567890123, 'alicew@example.com'); "
                                "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) "
                                "VALUES (5, 'Michael', 'Brown', '1995-07-20', '202 Birch St, IL', 5678901234, 'michaelbrown@example.com');";
    executeSQL(db, insertDataSQL);
    std::cout << "Records created successfully" << std::endl;
	
    printTableData(db);
	sqlite3_close(db);
}
