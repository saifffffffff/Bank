#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculator.h"
class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeOptions {eListCurrencies = 1, eFindCurrecy , eUpdateRate, eCurrencyCalculator, eMainMenu};
	
	static void _ShowListCurrenciesScreen(){
		clsListCurrenciesScreen::ShowListCurrenciesScreen();
	}
	static void _ShowFindCurrencyScreen(){
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen(){
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen(){
		clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
	}
	static void _GoBackToCurrncyExchangeMenu() {
		cout << "\nPress any key to go back to Currencies Menu...";
		system("pause>0");
		system("clear");
		ShowCurrencyExchangeScreen();
	}

	static void _PerformCurrecyExchageOption(enCurrencyExchangeOptions option) {


		switch (option) {
		
		case eListCurrencies:
			system("clear");
			_ShowListCurrenciesScreen();
			_GoBackToCurrncyExchangeMenu();
			break;
		
		case eFindCurrecy :
			system("clear");
			_ShowFindCurrencyScreen();
			_GoBackToCurrncyExchangeMenu();
			break;
		
		case eUpdateRate :
			system("clear");
			_ShowUpdateRateScreen();
			_GoBackToCurrncyExchangeMenu();
			break;
		
		case eCurrencyCalculator:
			system("clear");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrncyExchangeMenu();
			break;
		
		case eMainMenu:
			break;

		}

	}

public:
	static void ShowCurrencyExchangeScreen() {
		_DrawScreenHeader("\t Currency Exchange");
		
		cout << "\t[1] List Currencies.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Rate.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] MainMenu.\n";
		cout << "==================================\n";
		_PerformCurrecyExchageOption((enCurrencyExchangeOptions)clsInputValidate::ReadIntInRange(1, 5, "Enter [ 1 - 5 ] : ", "Please enter number between [ 1 - 5 ] : ", "invalid input, enter another one : "));
	}

};

