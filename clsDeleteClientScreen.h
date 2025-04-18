#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{
private:
	// each screen has its own print client method because it can differ from screen to another
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
	static string _ReadAccountNumber() {
		string AccountNumber = clsInputValidate::ReadString("Enter Account Number : ");
		while (!clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Not found, please enter another one : ");
		}
		return AccountNumber;
	}


public:
	static void ShowDeleteClientScreen() {
		
		if (!_CheckAccessRights(clsUser::pDeleteClient))
			return;
		
		_DrawScreenHeader("\t   Delete Client", enAlignment::Center);
		
		clsBankClient client = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientInfo(client);

		char WantToDelete = clsInputValidate::ReadChar("are you sure you want to delete this client (y) (n) ? ");

		if (tolower(WantToDelete) == 'y')
		{
			if (client.Delete())
				cout << "\nDeleted successfully :-)\n\n";
			else
				cout << "\nNot deleted :-(\n\n";
		}
	}


};

