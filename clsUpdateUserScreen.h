#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsUpdateUserScreen : protected clsScreen
{

private:
	static string _ReadUserName() {
		string UserName = clsInputValidate::ReadString("User name : ");
		while (!clsUser::DoesUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("There is no user with {" + UserName + "} user name, enter another one : ");
		}
		return UserName;
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

		}
		return permissions;
	}
	static void _ReadUserInfo(clsUser& user) {
		user.FirstName = clsInputValidate::ReadString("First name : ");
		user.LastName = clsInputValidate::ReadString("Last name : ");
		user.Email = clsInputValidate::ReadString("Email : ");
		user.PhoneNumber = clsInputValidate::ReadString("Phone number : ");
		user.Password = clsInputValidate::ReadString("Password : ");
		user.Permissions = _ReadPermissions();
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
	static void ShowUpdateUserScreen() {

		_DrawScreenHeader("\t   Update User", enAlignment::Center);

		string UserName = _ReadUserName();

		clsUser user = clsUser::Find(UserName);
		
		_PrintUserInfo(user);

		char WantToUpdate = clsInputValidate::ReadChar("\nAre you sure you want to update this user (y) (n) ? ");
		if (tolower(WantToUpdate))
		{
			_ReadUserInfo(user);
			clsUser::enSaveResult svResult;
			svResult = user.Save();


			switch (svResult)
			{
			case clsUser::SavedField_EmptyObj:
				cout << "\nUpdating user field, empty user.\n";
			
			case clsUser::SavedSuccessfuly:

				cout << "\nUpdated Successfully\n\n";

				_PrintUserInfo(user);
				cout << endl;
			}
		}
		else
			cout << "\nOperation cancelled\n";

	}

};

