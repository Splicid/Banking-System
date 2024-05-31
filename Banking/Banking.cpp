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

	Bank b;
	b.checkUserMembership(db);
	sqlite3_close(db);

}
