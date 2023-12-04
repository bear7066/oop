// Account.h
 
/* 
 * 
 *  Account class with name and balance data members, and a
 *  constructor and deposit function that each perform validation.
 *
 */


// function prototype declaration

#include <string>
using namespace std;

class Account {
public:
	// Account constructor with two parameters
	Account(string accountName, int initialBalance)
		:name{accountName}
		{
			if(initialBalance >0){
				balance = initialBalance;
			}
		}

	// Function that deposits (adds) only a valid amount to the balance
	void deposit(int depositAmount)
	{
		if(depositAmount > 0){
			balance = balance + depositAmount;
		}
	}

	// Return the account balance
	int getBalance() const
	{
		return balance;
	}

	// Setting names
	void setName(string accountName)
	{
		name = accountName;
	}

	// Return the name
	string coutName() const
	{
		return name;
	}

private:
	// Initila data member
	string name;
	int balance{0};        
};

















