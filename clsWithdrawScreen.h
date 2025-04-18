#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsWithdrawScreen : protected clsScreen
{
private:

	static void _PrintClientInfo(clsBankClient& client) {
		cout << "Client Card" << endl;
		cout << "-----------------------------" << endl;
		cout << "First Name      : " << client.FirstName << endl;
		cout << "Last Name       : " << client.LastName << endl;
		cout << "Email           : " << client.Email << endl;
		cout << "Phone Number    : " << client.PhoneNumber << endl;
		cout << "Account Number  : " << client.AccountNumber() << endl;
		cout << "PinCode         : " << client.PinCode << endl;
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "------------------------------" << endl;
	}

public:




	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\t  Withdraw Screen", enAlignment::Center);

		string AccountNumber = clsInputValidate::ReadString("Enter Client's account number : ");

		while (!clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Account number not found , enter another one : ");
		}
		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(client);

		double Amount = clsInputValidate::ReadDoubleInRange(0, INT_MAX, "\nEnter a Withdraw amount : ", "Please Enter a valid amout : ", "Please Enter a valid amout : ");

		
		char WantToWithdraw = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction (y) (n) ? ");

		if (tolower(WantToWithdraw) == 'y')
		{
			if (!client.Withdraw(Amount))
			{
				cout << "\nCannot withdraw, Insuffecient balance !\n\n";
				cout << "Amount to withdraw is : " << Amount << "\n";
				cout << "You Balance : " << client.AccountBalance << "\n\n";
			}
			
			else
			{
				cout << "\nAmount Withdrawed successfully !\n\n";
				cout << "New balance is " << client.AccountBalance << endl;
			}
		}

		else {
			cout << "\noperation cancelled\n";
		}

		

	}

};

