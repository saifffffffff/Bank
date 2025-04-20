#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:
	static void _PrintCurrencyInfo(clsCurrency& currency) {
		cout << "\nCurrency Card\n";
		cout << "==========================\n";
		cout << "County : " << currency.GetCountry() << endl;
		cout << "Code   : " << currency.GetCode() << endl;
		cout << "Name   : " << currency.GetName() << endl;
		printf("Rate     : %.3f\n", currency.GetRate());
		cout << "==========================\n";
	}
	static string _ReadCurrencyCode(string message) {
		string code = clsInputValidate::ReadString(message);
		while (!clsCurrency::DoesCurrencyExist(code))
			code = clsInputValidate::ReadString("Currency not found , enter another one : ");
		return code;
	}

public: 
	static void ShowUpdateCurrencyRateScreen() {
		_DrawScreenHeader("\t Upate Rate");
		 
		string Code = _ReadCurrencyCode("Enter Currency Code : ");
		clsCurrency currency = clsCurrency::FindByCode(Code);
		_PrintCurrencyInfo(currency);

		char WantToUpate = clsInputValidate::ReadChar("\nAre you sure you want to update this currency (y) (n) ? ");
		if (tolower(WantToUpate) == 'y')
		{
			double CurrencyNewRate = clsInputValidate::ReadDoubleInRange(0,INT_MAX,"\nEnter New Rate : ");
			currency.UpdateRate(CurrencyNewRate);
			cout << "\nUpdated Successfully :-)\n";
			_PrintCurrencyInfo(currency);
		}


	}

};

