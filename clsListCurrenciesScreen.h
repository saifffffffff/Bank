#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsListCurrenciesScreen : protected clsScreen
{
private:
	static void PrintCurrencyRecord(clsCurrency currncy) {
		cout << "\t |" << setw(31)<<left << currncy.GetCountry();
		cout << "| " << setw(8) <<left << currncy.GetCode();
		cout << "| " << setw(40) <<left << currncy.GetName();
		cout << "| " << setw(17) <<left << currncy.Rate << "|";

		
	}

public:
	static void ShowListCurrenciesScreen() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		
		_DrawScreenHeader("\t Currencies List", enAlignment::Center, "\t (221) Currency");


		cout << "\n\t " << "========================================================================================================\n";
		cout << "\t | " << setw(30) << left << "Country" << "| " << setw(8) << left << "Code" << "| " << setw(40) << left << "Name" << "| " << setw(17) << "Rate/(1$)" << "|";
		cout << "\n\t " << "========================================================================================================\n";

		for (clsCurrency & currency : vCurrencies) {
			PrintCurrencyRecord(currency);
			cout << endl;
		}

		cout << "\t " << "========================================================================================================\n";
	}
};

