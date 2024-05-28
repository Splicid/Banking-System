#include <iostream>
#include <string>
#include <cstdlib>
#include <sqlite3.h>


int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void executeCustomerSQL(sqlite3* db, const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth,
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

void executeAccountSQL(sqlite3* db, const int accountNumber, const double balance, const int accountHolderId)
{
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO ACCOUNTS (ID, ACCOUNT_NUMBER, BALANCE, ACCOUNT_HOLDER_ID) VALUES (?, ?, ?, ?);";
    char* errorMessage = 0;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    sqlite3_bind_int(stmt, 2, accountNumber);
    sqlite3_bind_double(stmt, 3, balance);
    sqlite3_bind_int(stmt, 4, accountHolderId);

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
