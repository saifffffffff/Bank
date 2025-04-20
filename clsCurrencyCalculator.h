#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculator : protected clsScreen
{
	static string _ReadCurrencyCode(string message) {
		string code = clsInputValidate::ReadString(message);
		while (!clsCurrency::DoesCurrencyExist(code))
			code = clsInputValidate::ReadString("Currency not found , enter another one : ");
		return code;
	}

public:
	static void ShowCurrencyCalculatorScreen() {

		_DrawScreenHeader("\t Currency Calculator");
		
		char WantToPerformAnotherOperation = 'n';
		do {
			string Currency1Code = _ReadCurrencyCode("\nEnter Currency 1 Code : ");
			string Currency2Code = _ReadCurrencyCode("\nEnter Currecy 2 Code : ");
			double AmountToConvert = clsInputValidate::ReadDoubleInRange(0, INT_MAX, "\nEnter Amout To Convert : ", "Invalid Input , Enter Amount To Convert", "Invalid Input , Enter Amount To Convert");
			clsCurrency currency1 = clsCurrency::FindByCode(Currency1Code), currency2 = clsCurrency::FindByCode(Currency2Code);

			double ConvertedAmount = currency1.ConvertAmountTo(AmountToConvert,currency2);

			cout << endl << AmountToConvert << " " << currency1.GetCode() << " = " << ConvertedAmount << " " << currency2.GetCode() << endl;
			
			WantToPerformAnotherOperation = clsInputValidate::ReadChar("\nDo you want to perform another operation (y) (n) ? ");
		
		} while (tolower(WantToPerformAnotherOperation) == 'y');

	}
};

