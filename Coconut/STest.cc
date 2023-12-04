
#include <iostream>
#include "Hello.h"
using namespace std;

int main() 
{
	Account account1{"Enret", 50};
	Account account2{"Harry", -20};

	// display initial balance 
	cout << "account1: " << account1.coutName() << " has balance $" 
		 << account1.getBalance() << endl;
	cout << "account2: " << account2.coutName() << " has balance $" 
		 << account2.getBalance() << endl << endl;
	
	// deposit money
	cout << "Input your deposit amount: ";
	int depositAmount;  cin >> depositAmount;
	cout << "adding..."<< endl << endl;
   	
	// depositMoney_Function 
	account1.deposit(depositAmount);
	cout <<	account1.coutName() << " has " << account1.getBalance()<<"$ now"<< endl;
	
	cout << "account1: " << account1.coutName() << " has balance $" 
		 << account1.getBalance() << endl;
	cout << "account2: " << account2.coutName() << " has balance $" 
		 << account2.getBalance() << endl << endl;
	
	return 0;
}
