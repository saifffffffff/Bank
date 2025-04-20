#pragma once
#include <iostream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsAddClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
	
	enum enMainMenuChoices {eShowClientList = 1, eAddNewClient , eDeleteClient , eUpdateClientInfo , eFindClient, eTransactions , eManageUsers , eLoginRegister, eCurrencyExchange, eLogout};
	static void _ShowClientListScreen(){
		clsClientListScreen::ShowClientList();
	}
	static void _ShowAddClientScreen(){
		clsAddClientScreen::ShowAddClientScreen();
	}
	static void _ShowDeleteClientScreen(){
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen(){
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen(){
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionsScreen() {
		clsTransactionsScreen::ShowTransactionsScreen();
	}
	static void _ShowManageUsersScreen() {
		clsManageUsersScreen::ShowManageUsersScreen();
	}
	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _Logout() {
		SystemUser = clsUser::Find("");
	}
	static void _ShowCurrencyExchangeScreen() {
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}
	static void _GoBackToMainMenu() {
		cout << "Press any key to back...";
		system("pause>0");
		system("clear");
		ShowMainScreen();
	}
	

	static void _PerformMainMenuOption(enMainMenuChoices choice) {

		system("clear");
	
		switch (choice) {

		case (eShowClientList):
			_ShowClientListScreen();
			_GoBackToMainMenu();
			break;

		case eAddNewClient:
			_ShowAddClientScreen();
			_GoBackToMainMenu();
			break;

		case eDeleteClient:
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;

		case eUpdateClientInfo:
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;

		case eFindClient:
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		
		case eTransactions:
			_ShowTransactionsScreen();
			_GoBackToMainMenu();
			break;

		case eManageUsers:
			_ShowManageUsersScreen();
			_GoBackToMainMenu();
			break;
		case eLoginRegister:
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		case eCurrencyExchange:
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenu();
			break;
		case eLogout:
			_Logout();
			break;
		}
	}

public:

	static void ShowMainScreen() {
		_DrawScreenHeader("\t    Main Menu");
		cout << "\t{1} Show Client List.\n";
		cout << "\t{2} Add New Client.\n";
		cout << "\t{3} Delete Client.\n";
		cout << "\t{4} Update Client Info.\n";
		cout << "\t{5} Find Client.\n";
		cout << "\t{6} Transactions.\n";
		cout << "\t{7} Manage Users.\n";
		cout << "\t{8} Login Register.\n";
		cout << "\t{9} Currency Exchange.\n";
		cout << "\t{10} Log Out.\n";
		cout << "==================================\n";

		_PerformMainMenuOption((enMainMenuChoices)clsInputValidate::ReadIntInRange(1, 10, "Enter ( 1 - 10 ) : ", "Please Enter Number Between 1 and 8 : ", "Invalid Input , enter again : "));

	}

};

/*

each screen in a seperate class

User Interface Layer ?? ????? ??? ???
 UI ??? Business/Logic Layer ??
(???? ??????? Desktop) ???? ?? ????? ???? ???????
????? ????? ??? ????????? B Layer ???

*/