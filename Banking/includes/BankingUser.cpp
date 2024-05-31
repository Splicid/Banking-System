#include <iostream>
#include <string>
#include <cstdlib>
#include <sqlite3.h>
#include <sodium.h>

// Include the BankingDBActions.cpp file
#include "BankingDBActions.cpp"


class Bank
{
private:
	double m_customerBalance;
	std::string password;
	int m_accountIdNumber;

public:
    std::string m_accountHolderFirst;
    std::string m_accountHolderLast;

    // Variables for users address
    std::string m_accountHolderAddress;
    std::string m_accountHolderCity;
    std::string m_accountHolderState;
	std::string m_fullAddress;
	std::string m_emailAddress;
	std::string m_phoneNumber;
    int m_accountHolderZip;


	Bank()
	{
		m_accountHolderFirst = "";
		m_customerBalance = 0;
		m_accountIdNumber = 1;
	}

	int checkUserMembership(sqlite3* db)
	{
		std::string answer;
		std::cout << "Do you have an account. yes/no: ";
		std::cin >> answer;
		if (answer == "yes")
		{
			userLogin(db);
			return 0;
		}
		newUser(db);
        return 0;
	}

	void userLogin(sqlite3* db)
	{
		std::string email;
		std::string password;
		std::cout << "Enter your email: ";
		std::cin >> email;
		std::cout << "Enter your password: ";
		std::cin >> password;

		// Check if the user exists
		if (checkUser(db, email, password))
		{
			std::cout << "Login successful" << std::endl;
			
		}
		else
		{
			std::cout << "Login failed" << std::endl;
		}
	}

	bool checkUser(sqlite3* db, const std::string& email, const std::string& password)
	{
		sqlite3_stmt* stmt;
		const char* sql = "SELECT * FROM ACCOUNTS WHERE ACCOUNT_EMAIL = ?;";
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_ROW) {
			std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		std::string hashedPassword = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		std::cout << "Hashed Password: " << hashedPassword << std::endl;
		return checkPassword(password, hashedPassword);
	}

    std::string dateCheck(std::string m_accountDate)
    {
        std::cout << "Enter Your date of birth (YYYY-MM-DD): ";
        std::getline(std::cin, m_accountDate);
        struct tm tm;   
        std::string s(m_accountDate);
        if (strptime(s.c_str(), "%Y-%m-%d", &tm))
            //std::cout << "Validate date" << std::endl;
            return m_accountDate;
        return dateCheck(m_accountDate);   
    }

	std::string getPassword()
	{
		// Getting the password
		std::cout << "Enter your password: ";
		std::cin >> password;

		// Checking the password
		std::string passwordCheck;
		std::cout << "Re-enter your password: ";
		std::cin >> passwordCheck;

		// Checking if the password is correct
		if (password != passwordCheck)
		{
			std::cout << "Passwords do not match. Please try again" << std::endl;
			getPassword();
		}

		return password;
	}

	std::string hashPassword(const std::string& password) 
	{
		// Define the size for the hashed password
		char hashedPassword[crypto_pwhash_STRBYTES];

		// Hash the password
		if (crypto_pwhash_str(
				hashedPassword,
				password.c_str(),
				password.size(),
				crypto_pwhash_OPSLIMIT_INTERACTIVE,
				crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
			throw std::runtime_error("Hashing failed: out of memory");
		}

		return std::string(hashedPassword);
	}

	bool checkPassword(const std::string& password, const std::string& hash) 
	{
		return crypto_pwhash_str_verify(
			hash.c_str(),
			password.c_str(),
			password.size()) == 0;
	}

	// void testCheckPassword()
	// {
	// 	std::string password = "password";
	// 	std::string hashedPassword = hashPassword(password);
	// 	std::cout << "Hashed Password: " << hashedPassword << std::endl;
	// 	std::cout << "Password is: " << checkPassword(password, hashedPassword) << std::endl;
	// }




	// This function will create a new user
	void newUser(sqlite3* db) {
		srand(time(0));
        std::cout << "--------------- Welcome to the Bank ---------------" << std::endl;

        std::cout << "Enter your first name: ";
        std::cin.ignore(); 
        std::getline(std::cin, m_accountHolderFirst);

        std::cout << "Enter your last name: ";
        std::getline(std::cin, m_accountHolderLast);

        std::cout << "Enter your email address: ";
        std::getline(std::cin, m_emailAddress);

        std::string password = getPassword();
        std::cin.ignore(); 

        std::cout << "Enter Address Line: ";
        std::getline(std::cin, m_accountHolderAddress);

        std::cout << "Enter your city: ";
        std::getline(std::cin, m_accountHolderCity);

        std::cout << "Enter your State: ";
        std::getline(std::cin, m_accountHolderState);

        std::cout << "Enter your Zip Code: ";
        std::cin >> m_accountHolderZip;
        std::cin.ignore();

        std::cout << "Enter your phone number: ";
        std::getline(std::cin, m_phoneNumber);

        std::cout << "--------------- Your account has been created ---------------" << std::endl;
        std::cout << "Name: " << m_accountHolderFirst << " " << m_accountHolderLast << std::endl;
        std::cout << "Address: " << m_accountHolderAddress << std::endl;
        std::cout << "City: " << m_accountHolderCity << std::endl;
        std::cout << "State: " << m_accountHolderState << std::endl;
        std::cout << "Zip Code: " << m_accountHolderZip << std::endl;

        std::string m_fullAddress = m_accountHolderAddress + " " + m_accountHolderCity + " " + m_accountHolderState + " " + std::to_string(m_accountHolderZip);
        std::string m_HashedPassword = hashPassword(password);

        executeCustomerSQL(db, m_accountHolderFirst, m_accountHolderLast, m_fullAddress, m_phoneNumber);
        executeAccountSQL(db, rand() % 1000 + 1, m_emailAddress, m_HashedPassword);

		//close db
		sqlite3_close(db);
    }

    ~Bank()
    {
        std::cout << "Destroying Info" << std::endl;
    }
};
