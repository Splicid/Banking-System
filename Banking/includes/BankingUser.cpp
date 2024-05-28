#include <iostream>
#include <string>
#include <cstdlib>
#include <sqlite3.h>
#include "BankingDBActions.cpp"


class Bank
{
private:
	double m_customerBalance;
	int m_accountIdNumber;

public:
    std::string m_accountHolderFirst;
    std::string m_accountHolderLast;
    std::string m_accountHolderDate;

    // Variables for users address
    std::string m_accountHolderAddress;
    std::string m_accountHolderCity;
    std::string m_accountHolderState;
    int m_accountHolderZip;



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

	void newUser()
	{
        // Getting account info 
        // First Name
		std::cout << "Enter your first name: ";
		std::cin.ignore();
		std::getline(std::cin, m_accountHolderFirst);

        // Last Name
        std::cout << "Enter your last name: ";
        std::getline(std::cin, m_accountHolderLast);

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

		
	}

	int accountActionable()
	{
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