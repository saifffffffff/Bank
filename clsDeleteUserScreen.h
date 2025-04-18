#pragma once
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsDeleteUserScreen : protected clsScreen
{

private:
	static string _ReadUserName() {
		string UserName = clsInputValidate::ReadString("User name : ");
		while (!clsUser::DoesUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("There is no user with {" + UserName + "} user name, enter another one : ");
		}
		return UserName;
	}

	static void _PrintUserInfo(clsUser& user) {
		
		cout << "\nUser Card" << endl;
		cout << "-----------------------------" << endl;
		cout << "User Name    : " << user.Username << endl;
		cout << "First Name   : " << user.FirstName << endl;
		cout << "Last Name    : " << user.LastName << endl;
		cout << "Email        : " << user.Email << endl;
		cout << "Phone Number : " << user.PhoneNumber << endl;
		cout << "Password     : " << user.Password << endl;
		cout << "Permissions  : " << user.Permissions << endl;
		cout << "------------------------------" << endl;
	}
public:

	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\t    Delete User", enAlignment::Center);
		
		string UserName = _ReadUserName();
		clsUser user = clsUser::Find(UserName);
		
		_PrintUserInfo(user);

		char WantToDelete = clsInputValidate::ReadChar("\nAre you sure you want to delete this user (y) (n) ? ");
		if(tolower(WantToDelete) == 'y' )
		{
			if (user.Delete())
				cout << "\nDeleted successfully.\n\n";
			else
				cout << "\nError, Not Deleted.\n";
		}
		else
		{
			cout << "\nOperation canceled\n\n";
		}

		
	}

};

