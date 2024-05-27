#include <iostream>
#include <string>
#include <cstdlib>
#include <sqlite3.h>



class Bank
{
private:
	double m_customerBalance;
	int m_accountIdNumber;

public:
    std::string m_accountHolderFirst;
    std::string m_accountHolderLast;
    std::string m_accountHolderDate;


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

        std::cout << "Enter Your date of birth (YYYY-MM-DD)";
        std::getline(std::cin, m_accountDate);
        struct tm tm;   
        std::string s(m_accountDate);
        if (strptime(s.c_str(), "%Y-%m-%d", &tm))
            //std::cout << "Validate date" << std::endl;
            return m_accountDate;
        return "Invalid Date";
         
    }

	std::string newUser()
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
        std::cout << date << std::endl;

        // Address
        //std::cout << "Enter your address" << std::endl;

		return m_accountHolderDate;
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