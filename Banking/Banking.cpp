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

	const char* sql = "CREATE TABLE CUSTOMERS(" \
	"ID INT PRIMARY KEY		NOT NULLM" \
	"FIRST_NAME		TEXT 	NOT NULL," \
	"LAST_NAME 		TEXT 	NOT NULL," \
	"DATE_OF_BIRTH	DATE,"	\
	"ADDRESS 		TEXT	NOT NULL," \
	"PHONE_NUMBER	INT		NOT NULL," \
	"EMAIL			TEXT	NOT NULL);";
	
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sqlite3_close(db);
}
