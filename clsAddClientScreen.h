#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsAddClientScreen : protected clsScreen
{

private:
	static void _ReadClientInfo(clsBankClient& client) {
		client.FirstName = clsInputValidate::ReadString("Enter first name : ");
		client.LastName = clsInputValidate::ReadString("Enter last name : ");
		client.PhoneNumber = clsInputValidate::ReadString("Enter phone number : ");
		client.Email = clsInputValidate::ReadString("Enter Email : ");
		client.PinCode = clsInputValidate::ReadString("Enter pincode : ");
		client.AccountBalance = clsInputValidate::ReadDouble("Enter account balance : ");
	}
	static void _PrintClientInfo(clsBankClient& client) {
		cout << "New Client Card" << endl;
		cout << "------------------------------" << endl;
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
		while (clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Account Number already exist, Enter another one : ");
		}
		return AccountNumber;
	}
public:
	static void ShowAddClientScreen() {

		if (!_CheckAccessRights(clsUser::pAddNewClient))
			return;

		_DrawScreenHeader("\t     Add Client", enAlignment::Center);

		clsBankClient client = clsBankClient::GetAddClientObject(_ReadAccountNumber());

		_ReadClientInfo(client);

		clsBankClient::enSaveResults svResult = client.Save();

		switch (svResult)
		{
		case clsBankClient::saveField_EmptyObject:
			cout << "\nfield , empty client :-(\n\n";
			break;
		case clsBankClient::saveField_AccountNumExist:
			cout << "\nfield , account number already exist :-(\n\n";
			break;
		case clsBankClient::saveSucceeded:
			cout << "\nAdded Successfuly :-)\n\n";
			break;

		}

		_PrintClientInfo(client);

	}

};

