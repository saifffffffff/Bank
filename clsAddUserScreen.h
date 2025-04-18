#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <vector>

class clsAddUserScreen : protected clsScreen
{

private:
	static void _ReadUserInfo(clsUser & user){
		user.FirstName = clsInputValidate::ReadString("First name : ");
		user.LastName = clsInputValidate::ReadString("Last name : ");
		user.Email = clsInputValidate::ReadString("Email : ");
		user.PhoneNumber = clsInputValidate::ReadString("Phone number : ");
		user.Password = clsInputValidate::ReadString("Password : ");
		user.Permissions = _ReadPermissions();
	}
	static short _ReadPermissions() {
		char WantToGiveUserFullAccess = clsInputValidate::ReadChar("Do you want to give full access (y/n) ? ");
		short permissions = 0;

		if (tolower(WantToGiveUserFullAccess) == 'y')
		{
			permissions = -1;
		}

		else {
			cout << "\nDo you want to give access to : \n\n";

			permissions = 0;

			char WantToGiveAccess;

			WantToGiveAccess = clsInputValidate::ReadChar("Show Client List (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pShowClientList;

			WantToGiveAccess = clsInputValidate::ReadChar("Add New Client (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pAddNewClient;

			WantToGiveAccess = clsInputValidate::ReadChar("Delete Client (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pDeleteClient;

			WantToGiveAccess = clsInputValidate::ReadChar("Update Client (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pUpdateClient;

			WantToGiveAccess = clsInputValidate::ReadChar("Find Client (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pFindClient;

			WantToGiveAccess = clsInputValidate::ReadChar("Transactions (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pTransactions;

			WantToGiveAccess = clsInputValidate::ReadChar("Manage Users (y / n) ? ");

			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pManageUsers;

			WantToGiveAccess = clsInputValidate::ReadChar("Show Login register List (y / n) ? ");
			
			if (tolower(WantToGiveAccess) == 'y')
				permissions |= clsUser::enPermissions::pShowLoginRegister;
		
		}
		return permissions;
	}
	static void _PrintUserInfo(clsUser& user) {
		cout << "User Card" << endl;
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
	static string _ReadUserName() {
		string UserName = clsInputValidate::ReadString("User name : ");
		while (clsUser::DoesUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("User with {" + UserName + "} user name already exists, enter another one : ");
		}
		return UserName;
	}


public:

	static void ShowAddUserScreen() {
		_DrawScreenHeader("\t   Add User");

		
		string UserName = _ReadUserName();

		clsUser user = clsUser::GetAddUserObject(UserName);
		
		_ReadUserInfo(user);
		
		clsUser::enSaveResult svResult;
		svResult = user.Save();
		
		if (svResult == clsUser::SavedField_EmptyObj)
			cout << "\nAdding new user field, empty user.\n";
		else if (svResult == clsUser::SaveField_UserExists)
			cout << "\nAddinf new user field, user already exists.\n";
		else
		{
			cout << "\nAdded Successfully\n\n";
			
			_PrintUserInfo(user);
			cout << endl;
		}
			

	}
};

