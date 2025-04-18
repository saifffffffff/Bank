#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindUserScreen : protected clsScreen
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
		cout << "------------------------------\n" << endl;
	}

public:
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t   Find User", enAlignment::Center);
		string Username = _ReadUserName();
		clsUser user = clsUser::Find(Username);
		if (!user.IsEmpty())
			_PrintUserInfo(user);
		else
			cout << "\nUser Not Found :-(\n\n";
	}

};

