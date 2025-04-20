#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsFindCurrencyScreen : protected clsScreen
{
	static void _PrintCurrencyInfo(clsCurrency & currency) {
		cout << "Currency Card\n";
		cout << "==========================\n";
		cout << "County : " << currency.GetCountry() << endl;
		cout << "Code   : " << currency.GetCode() << endl;
		cout << "Name   : " << currency.GetName() << endl;
		printf("Rate     : %.3f\n", currency.GetRate());
		cout << "==========================\n";
	}

	static void _ShowResult(clsCurrency & currency) {
		if (!currency.IsEmpty())
		{
			cout << "\nFound :-) \n\n";
			_PrintCurrencyInfo(currency);
		}

		else
			cout << "\nNot Found :-( \n";

	}

	enum enFindingMethods {eFindByCountry =1, eFindByCode};
public:
	static void ShowFindCurrencyScreen() {
		
		_DrawScreenHeader("\t Find Currency");
		
		enFindingMethods ChooseFindingMethod = (enFindingMethods)clsInputValidate::ReadIntInRange(1, 2, "[1] Find Currecy By Country [2] Find Currency By Code : ", "Invalid Input, [1] Find Currecy By Country [2] Find Currency By Code :  ","Invalid Input, [1] Find Currecy By Country [2] Find Currency By Code :  ");
		string Option;

		if (ChooseFindingMethod == enFindingMethods::eFindByCode) {
			Option = clsInputValidate::ReadString("Currency Code : ");
			clsCurrency currency = clsCurrency::FindByCode(Option);
			_ShowResult(currency);
			
		}

		if (ChooseFindingMethod == enFindingMethods::eFindByCountry) {
			Option = clsInputValidate::ReadString("Currency Country : ");
			clsCurrency currency = clsCurrency::FindByCountry(Option);
			_ShowResult(currency);	
		}

	}



};

