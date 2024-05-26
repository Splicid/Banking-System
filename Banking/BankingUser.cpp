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

	std::string newUser()
	{
		std::cout << "Enter your first name: ";
		std::cin.ignore();

        //Getting account info 
		std::getline(std::cin, m_accountHolderFirst);
        
        std::cout << "Enter you last name: ";
        std::getline(std::cin, m_accountHolderLast);
		std::cout << m_accountHolderFirst << std::endl;
		return m_accountHolderFirst;
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