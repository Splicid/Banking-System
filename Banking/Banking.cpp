#include <iostream>
#include <string>
#include <cstdlib>
#include "BankingUser.cpp"
#include <sqlite3.h>


int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void executeSQL(sqlite3* db, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth,
 const std::string& address, const std::string phoneNumber, const std::string email)
{
	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO CUSTOMERS (ID, FIRST_NAME, LAST_NAME, DATE_OF_BIRTH, ADDRESS, PHONE_NUMBER, EMAIL) VALUES (?, ?, ?, ?, ?, ?, ?);";
	char* errorMessage = 0;
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	
	if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
	sqlite3_bind_text(stmt, 2, firstName.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, lastName.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, dateOfBirth.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, address.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, phoneNumber.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, email.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

	sqlite3_finalize(stmt);
}

void executeTableSQL(sqlite3* db, const char* sql)
{
	char* errorMessage = 0;
	int rc = sqlite3_exec(db, sql, 0 , 0, &errorMessage);
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
                  << sqlite3_column_text(stmt, 5) << " | "
                  << sqlite3_column_text(stmt, 6) << std::endl;
    }

    sqlite3_finalize(stmt);
}

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
	// executeTableSQL(db, createTableSQL);
	// executeSQL(db, "Luis", "Abreu", "1999-25-02", "92 South 10th", "347-661-6555", "luistest@gmail.com");
	//executeTableSQL(db, createTableSQL);

    printTableData(db);
	sqlite3_close(db);

	Bank b;
}
