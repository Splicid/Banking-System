#include <iostream>
#include <string>
#include <cstdlib>
#include <sqlite3.h>
#include "BankingDBActions.cpp"
#include <sodium.h>

class Bank
{
private:
	double m_customerBalance;
	std::string password;
	int m_accountIdNumber;

public:
    std::string m_accountHolderFirst;
    std::string m_accountHolderLast;
    std::string m_accountHolderDate;

    // Variables for users address
    std::string m_accountHolderAddress;
    std::string m_accountHolderCity;
    std::string m_accountHolderState;
	std::string m_fullAddress;
	std::string m_emailAddress;
    int m_accountHolderZip;
	sqlite3* db;



	Bank()
	{
		m_accountHolderFirst = "";
		m_customerBalance = 0;
		m_accountIdNumber = 1;
	}

    void customerBalance()
	{
		std::cout << "Your currently have: " << m_customerBalance << std::endl;
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
		newUser();
        return 0;
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

	void testCheckPassword()
	{
		std::string password = "password";
		std::string hashedPassword = hashPassword(password);
		std::cout << "Hashed Password: " << hashedPassword << std::endl;
		std::cout << "Password is: " << checkPassword(password, hashedPassword) << std::endl;
	}
	void newUser()
	{
        // Getting account info 
		std::cout << "--------------- Welcome to the Bank ---------------" << std::endl;
        // First Name
		std::cout << "Enter your first name: ";
		std::cin.ignore();
		std::getline(std::cin, m_accountHolderFirst);

        // Last Name
        std::cout << "Enter your last name: ";
        std::getline(std::cin, m_accountHolderLast);

		// Email Address
		std::cout << "Enter your email address: ";
		std::cin >> m_emailAddress;

		// Password 
		std::string password = getPassword();

        // Date of Birth
        std::string date = dateCheck(m_accountHolderDate);

        // Address Prompts
        std::cout << "Enter Address Line: ";
        std::getline(std::cin, m_accountHolderAddress);
        std::cout << "Enter your city: ";
        std::getline(std::cin, m_accountHolderAddress);
        std::cout << "Enter your State: ";
		std::getline(std::cin, m_accountHolderState);
		std::cout << "Enter your Zip Code: ";
		std::cin >> m_accountHolderZip;

		// Displaying the information
		std::cout << "--------------- Your account has been created ---------------" << std::endl;
		std::cout << "Name: " << m_accountHolderFirst << " " << m_accountHolderLast << std::endl;
		std::cout << "Date of Birth: " << m_accountHolderDate << std::endl;
		std::cout << "Address: " << m_accountHolderAddress << std::endl;
		std::cout << "City: " << m_accountHolderCity << std::endl;
		std::cout << "State: " << m_accountHolderState << std::endl;
		std::cout << "Zip Code: " << m_accountHolderZip << std::endl;

		std::string m_fullAddress = m_accountHolderAddress + " " + m_accountHolderCity + " " + m_accountHolderState + " " + std::to_string(m_accountHolderZip);
		// Inserting the information into the database
		
	}

	int accountActionable()
	{
		executeCustomerSQL(db, m_accountHolderFirst, m_accountHolderLast, m_accountHolderDate, m_fullAddress, "1234567890", m_emailAddress);
		return 0;
	}

    ~Bank()
    {
        std::cout << "Destroying Info" << std::endl;
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