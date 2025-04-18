#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
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
	static void _ReadClientInfo(clsBankClient& client) {
		client.FirstName = clsInputValidate::ReadString("Enter first name : ");
		client.LastName = clsInputValidate::ReadString("Enter last name : ");
		client.PhoneNumber = clsInputValidate::ReadString("Enter phone number : ");
		client.Email = clsInputValidate::ReadString("Enter Email : ");
		client.PinCode = clsInputValidate::ReadString("Enter pincode : ");
		client.AccountBalance = clsInputValidate::ReadDouble("Enter account balance : ");
	}
	static string _ReadAccountNumber() {
		string AccountNumber = clsInputValidate::ReadString("Enter Account Number : ");
		while (!clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Not found, please enter another one : ");
		}
		return AccountNumber;
	}
public:


	static void ShowUpdateClientScreen() {


		if (!_CheckAccessRights(clsUser::pUpdateClient))
			return;

		_DrawScreenHeader("\t  Upate Clinet",enAlignment::Center);

		clsBankClient client = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientInfo(client);

		char WantToUpdate = clsInputValidate::ReadChar("Are you sure you want to update this client (y) (n) ? ");

		if (tolower(WantToUpdate) == 'y')
		{
			cout << "\nUpdate Client Info\n-------------------\n";
			_ReadClientInfo(client);

			clsBankClient::enSaveResults svResult = client.Save();

			switch (svResult) {
			case clsBankClient::enSaveResults::saveSucceeded:
				cout << "\nsaved successfuly :-)\n";
				_PrintClientInfo(client);
				break;

			case clsBankClient::enSaveResults::saveField_EmptyObject:
				cout << "\nfield :-(\n";
			}
		}
	}


};

