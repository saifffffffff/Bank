#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"



class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login() {
		
		string Username, Password;
		bool LoginField = false;
		short attempts = 3;
		do {

			if (LoginField)
			{
				 
				if (--attempts == 0)
				{
					cout << "\nYou are locked!!!\n";
					return false;
				}

				cout << "\nInvalid Username/Password.\n";
				cout << "You have " << attempts << " trial" << (attempts == 1 ? " " : "s ") << "to log in.\n\n";
			}

			Username = clsInputValidate::ReadString("Enter user name : ");
			Password = clsInputValidate::ReadString("Enter password : ");

			SystemUser = clsUser::Find(Username, Password);

			LoginField = SystemUser.IsEmpty();

		} while (LoginField);

		system("clear");
		SystemUser.RegisterLogin();
		clsMainScreen::ShowMainScreen();
		return true;
	}

public:

	static bool ShowLoginScreen() {
		system("clear");
		_DrawScreenHeader("\t     Log in", enAlignment::Center);
		return _Login();
		

	}

};

