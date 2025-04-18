#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDepositScreen :
    protected clsScreen
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

    static void ShowDepositScreen() {

        _DrawScreenHeader("\t  Deposit Screen",enAlignment::Center);
        
        string AccountNumber = clsInputValidate::ReadString("Enter Client's account number : ");

        while (!clsBankClient::DoesClientExist(AccountNumber)) {
            AccountNumber = clsInputValidate::ReadString("Account number not found , enter another one : ");
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(client);

		double Amount = clsInputValidate::ReadDoubleInRange(0, INT_MAX, "Enter Deposit amount : ", "Please Enter a valid amout : ", "Please Enter a valid amout : ");

		char WantToDeposit = clsInputValidate::ReadChar("Are you sure you want to perform this transaction (y) (n) ? ");

		if (tolower(WantToDeposit) == 'y')
		{
			client.Deposit(Amount);
			cout << "Amount Deposited successfully !\n\n";
			cout << "New balance is " << client.AccountBalance << endl;
		}
		else {
			cout << "operation cancelled\n";
		}




    }
};

