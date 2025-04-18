#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
class clsTransferScreen : protected clsScreen
{

private:
	static void _PrintClientInfo(clsBankClient& client) {
		cout << "-----------------------------" << endl;
		cout << "Full Name       : " << client.FullName() << endl;
		cout << "Email           : " << client.Email << endl;
		cout << "Phone Number    : " << client.PhoneNumber << endl;
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "------------------------------" << endl;
	}
	static string _ReadAccountNumber(string message) {
		string AccountNumber = clsInputValidate::ReadString(message);
		while (!clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Not found, please enter another one : ");
		}
		return AccountNumber;
	}
public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t   Transfer", enAlignment::Center);
		
		clsBankClient SenderClient = clsBankClient::Find(_ReadAccountNumber("Enter the sender client account number : "));
		cout << "\nSender Cleint Card\n";
		_PrintClientInfo(SenderClient);
		cout << "\n";

		clsBankClient RecieverClient = clsBankClient::Find(_ReadAccountNumber("Enter the reciever client account number : "));
		cout << "\nReciever Client Card\n";
		_PrintClientInfo(RecieverClient);
		cout << "\n";

		double amount = clsInputValidate::ReadDoubleInRange(0, INT_MAX, "Enter the transfer amount : ", "Invalid amount , enter again : ", "Invalid input , enter again : ");

		while (amount > SenderClient.AccountBalance)
			amount = clsInputValidate::ReadDoubleInRange(0, INT_MAX, "Amount Exceeds the available Balance, Enter another one : ", "Invalid amount , enter again : ", "Invalid input , enter again : ");


		char WantToTransfer = clsInputValidate::ReadChar("Are you sure you want to perform this transaction (y) (n) ? ");

		if (tolower(WantToTransfer) == 'y' )
		{
			if (SenderClient.Transfer(amount,RecieverClient))
			{
				cout << "\nDone successflly :-)\n";
				cout << "\nSender Cleint Card\n";
				_PrintClientInfo(SenderClient);

				cout << "\nReciever Client Card\n";
				_PrintClientInfo(RecieverClient);
				cout << '\n';
			}
				
			else
				cout << "Error :-(\n\n";
		}


	}

};

