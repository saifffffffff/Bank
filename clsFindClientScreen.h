#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsFindClientScreen :
    protected clsScreen
{

private:
	static void _PrintClientInfo(clsBankClient& client) {
		cout << "\nClient Card" << endl;
		cout << "-----------------------------" << endl;
		cout << "First Name      : " << client.FirstName << endl;
		cout << "Last Name       : " << client.LastName << endl;
		cout << "Email           : " << client.Email << endl;
		cout << "Phone Number    : " << client.PhoneNumber << endl;
		cout << "Account Number  : " << client.AccountNumber() << endl;
		cout << "PinCode         : " << client.PinCode << endl;
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "------------------------------\n" << endl;
	}
	static string _ReadAccountNumber() {
		string AccountNumber = clsInputValidate::ReadString("Enter Account Number : ");
		while (!clsBankClient::DoesClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Not found, please enter another one : ");
		}
		return AccountNumber;
	}
public:

    static void ShowFindClientScreen() {
		
		if (!_CheckAccessRights(clsUser::pFindClient))
			return;
		
		_DrawScreenHeader("\t  Find Client", enAlignment::Center);
		
        clsBankClient client = clsBankClient::Find(_ReadAccountNumber());
        
		if(!client.IsEmpty())
			_PrintClientInfo(client);
		else 
			cout << "Client Not Found" << endl;
    }
};

