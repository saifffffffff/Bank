#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{

private:


	static void _ShowListUsersScreen() {
		clsListUsersScreen::ShowListUsersScreen();

	}
	static void _ShowAddUsersScreen() {
		clsAddUserScreen::ShowAddUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}
	static void _GoBackToManageUsersScreen() {
		cout << "Press any key to back...";
		system("pause>0");
		system("clear");
		ShowManageUsersScreen();
	}

	enum enManageUsersOptions {ListUsers = 1, AddUser, DeleteUser,UpdateUser, FindUser, MainMenu };
	static void _PerformManageUsersScreenOption(enManageUsersOptions choice) {
		

		switch (choice)
		{
		case clsManageUsersScreen::ListUsers:
			system("clear");
			_ShowListUsersScreen();
			_GoBackToManageUsersScreen();
			break;
		case clsManageUsersScreen::AddUser:
			system("clear");
			_ShowAddUsersScreen();
			_GoBackToManageUsersScreen();
			break;
		case clsManageUsersScreen::DeleteUser:
			system("clear");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersScreen();
			break;

		case clsManageUsersScreen::UpdateUser:
			system("clear");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersScreen();
			break;
		case clsManageUsersScreen::FindUser:
			system("clear");
			_ShowFindScreen();
			_GoBackToManageUsersScreen();
			break;
		case clsManageUsersScreen::MainMenu:
			//_GoBackToMainMenu();
			break;
		}
	}
public:
	static void ShowManageUsersScreen() {
		
		if (!_CheckAccessRights(clsUser::pManageUsers))
			return;
		
		_DrawScreenHeader("\t  Manage Users");

		cout << "\t{1} List Users.\n" ;
		cout << "\t{2} Add New User.\n";
		cout << "\t{3} Delete User.\n";
		cout << "\t{4} Update User.\n";
		cout << "\t{5} Find User.\n";
		cout << "\t{6} Main Menu\n";
		cout << "==================================\n";
		_PerformManageUsersScreenOption((enManageUsersOptions)clsInputValidate::ReadIntInRange(1,6,"Enter ( 1 - 6 ) : ", "Please enter a number between ( 1 - 6 ) :", "Please enter a valid input : "));

	}
};

