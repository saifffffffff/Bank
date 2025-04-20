#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "GlobalFiles.h"
#include "clsString.h"

using namespace std;

class clsCurrency
{

private:
	string _Country, _Code, _Name;
	double _Rate;
	enum enMode {Empty, Update};
	enMode _Mode;
	

	void _Update() {
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFileToVector();

		for (clsCurrency& currency : vCurrencies)
			if (currency.GetCode() == this->_Code) {
				currency._Rate = this->_Rate;
				break;
			}

		_LoadCurrencyDataFromVectorToFile(vCurrencies);
	}
	static clsCurrency _ConvertLineToCurrencyObject(string line) {
		vector <string> vCurrencyData = clsString::Split(line, FileSeperator);
		clsCurrency currency(Update,vCurrencyData.at(0),
			vCurrencyData.at(1),
			vCurrencyData.at(2),
			stod(vCurrencyData.at(3))
		);

		return currency;
	}
	static string _ConvertCurrecyObjectToLine(clsCurrency & currency ) {
		string line = currency.GetCountry() + FileSeperator;
		line += currency.GetCode() + FileSeperator;
		line += currency.GetName() + FileSeperator;
		line += to_string(currency.GetRate()) + FileSeperator;
		return line;
	}
	static vector <clsCurrency> _LoadCurrencyDataFromFileToVector(){
		fstream file(CurrenciesFile, ios::in);
		vector <clsCurrency> vCurrencies ;

		if (file.is_open())
		{
			string line;
			while (getline(file, line)) {
				vCurrencies.push_back(_ConvertLineToCurrencyObject(line));
			}

			file.close();
		}

		return vCurrencies;
	}
	static void _LoadCurrencyDataFromVectorToFile(vector <clsCurrency> & vCurrencies){
		fstream file(CurrenciesFile, ios::out);
		if (file.is_open()) {
			for (clsCurrency& currency : vCurrencies)
				file << _ConvertCurrecyObjectToLine(currency) << endl;
			file.close();
		}

	}
	static clsCurrency _GetEmptyCurrencyObj() {
		return clsCurrency(Empty, "", "", "", 0);
	}



public:

	clsCurrency(enMode Mode ,string Country, string Code, string Name, double Rate) {
		_Mode = Mode;
		_Country = Country;
		_Code = Code;
		_Name = Name;
		_Rate = Rate;
	}

	string GetCountry() { return _Country; }
	string GetCode() { return _Code; }
	string GetName() { return _Name; }

	double GetRate() { return _Rate; }
	void UpdateRate(double NewRate) { 
		_Rate = NewRate; 
		_Update();
	}
	__declspec(property(get = GetRate, put = SetRate)) double Rate;
	
	static vector <clsCurrency> GetCurrenciesList() {
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFileToVector();
		return vCurrencies;
	}
	
	static clsCurrency FindByCode(string Code){
		
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFileToVector();
		
		for (clsCurrency & currency : vCurrencies) 
			if (currency.GetCode() == clsString::UpperAllString(Code))
				return currency;
		
		return _GetEmptyCurrencyObj();

	}
	static clsCurrency FindByCountry(string Country){
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFileToVector();

		for (clsCurrency& currency : vCurrencies)
			if (clsString::UpperAllString(currency.GetCountry()) == clsString::UpperAllString(Country))
				return currency;
		return _GetEmptyCurrencyObj();

	}

	bool IsEmpty() {
		return (_Mode == enMode::Empty);
	}
	static bool DoesCurrencyExist(string Code) {
		clsCurrency currency = FindByCode(Code);
		return !currency.IsEmpty();
	}

	double ConvertToUSD(double Amount) {
		return (Amount / _Rate);
	}

	double ConvertAmountTo( double AmoutToConvert , clsCurrency CurrencyToConvertTo) {
		
		double AmountInUsd = ConvertToUSD(AmoutToConvert);
		
		if (CurrencyToConvertTo.GetCode() == "USD")
			return AmountInUsd;

		return AmountInUsd * CurrencyToConvertTo.Rate;
	}
	

};

