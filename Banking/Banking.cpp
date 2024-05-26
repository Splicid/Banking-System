#include <iostream>
#include <string>


class Bank
{
private:
	std::string m_accountHolderName;
	double m_customerBalance;
	int accountNumber;

public:

	void customerBalance(double balance)
	{
		std::cout << "Your currently have: " << balance << std::endl;
	}
};


int main()
{
	Bank bank;
	bank.customerBalance(30);
}