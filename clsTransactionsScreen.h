#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsMainScreen.h"
#include "clsTransferLogScreen.h"


class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionChoices { Deposit = 1, Withdraw, TotalBalances, Transfer,ShowTransferLog, MainMenu };


	static void _DepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}
	static void _WithDrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _TotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}
	static void _TransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}
	static void _TransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void _BackToTransactionMenu() {
		cout << "Press any key to back...";
		system("pause>0");
		system("clear");
		ShowTransactionsScreen();
	}
	static void _PerformTransactionMenuOption(enTransactionChoices choice) {
		switch (choice)
		{
		case enTransactionChoices::Deposit:
			system("clear");
			_DepositScreen();
			_BackToTransactionMenu();
			break;
		case enTransactionChoices::Withdraw:
			system("clear");
			_WithDrawScreen();
			_BackToTransactionMenu();
			break;
		case enTransactionChoices::TotalBalances:
			system("clear");
			_TotalBalancesScreen();
			_BackToTransactionMenu();
			break;
		case enTransactionChoices::Transfer:
			system("clear");
			_TransferScreen();
			_BackToTransactionMenu();
			break;
		case enTransactionChoices::ShowTransferLog:
			system("clear");
			_TransferLogScreen();
			_BackToTransactionMenu();
		case clsTransactionsScreen::MainMenu:
			break;
		}
	}
public:
	static void ShowTransactionsScreen () {
		
		if (!_CheckAccessRights(clsUser::pTransactions))
			return;

		_DrawScreenHeader("\t  Transactions");
		cout << "\t[1] Deposit.\n";
		cout << "\t[2] Withdraw.\n";
		cout << "\t[3] Total Balances.\n";
		cout << "\t[4] Transfer.\n";
		cout << "\t[5] Show Transfer Log.\n";
		cout << "\t[6] Main Menu.\n";
		cout << "==================================\n";
		_PerformTransactionMenuOption((enTransactionChoices)clsInputValidate::ReadIntInRange(1, 6, "Enter ( 1 - 6 ) : ", "Please enter number between ( 1 - 5 ) : ", "Invalid Input , enter another choice : "));
	
	}

};

