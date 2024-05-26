#include <iostream>
#include <string>


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
		m_accountHolderName = "Empty";
		m_customerBalance = 0;
		m_accountNumber = 1;
	}

	std::string newUser()
	{
		std::cout << "Enter your full name: " << std::endl;
		std::cin >> m_accountHolderName;
		return m_accountHolderName;
	}

	int checkUserMembership()
	{
		std::string answer;
		std::cout << "Do you have an account. yes/no: " << std::endl;
		std::cin >> answer;
		if (answer == "yes")
		{
			return true;
		}
		else {
			std::cout << newUser();
		}
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
	char* newUser()
	{
		std::cout << "Enter your full name";
		std::cin >> m_accountHolderName;
	}
	
};



int main()
{
	Bank bank;
	bank.checkUserMembership();
}