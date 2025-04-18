#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "GlobalFiles.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;
	enum enMode {EmptyMode, UpdateMode, AddNewMode};
	enMode _Mode;
	
	void _Update() {
		vector <clsBankClient> _vClients = _LoadClientsDataFromFileToVector();

		for (clsBankClient& client : _vClients) {
			if (client.AccountNumber() == AccountNumber()) {
				client = *this;
			}
		}

		_LoadClientsDataFromVectorToFile(_vClients);

	}
	void _Add() {
		AddDataLineToFile(_ConvertClientObjectToLine(*this,FileSeperator));
	}
	
	
	static void AddDataLineToFile(string DataLine) {
		fstream file(ClientsFile, ios::app | ios::out);
		if (file.is_open())
		{
			file << DataLine << endl;
			file.close();
		}
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
		string strClientRecord = "";
		strClientRecord += Client.FirstName + Seperator;
		strClientRecord += Client.LastName + Seperator;
		strClientRecord += Client.Email + Seperator;
		strClientRecord += Client.PhoneNumber + Seperator;
		strClientRecord += Client.AccountNumber() + Seperator;
		strClientRecord += Client.PinCode + Seperator;
		strClientRecord += to_string(Client.AccountBalance);

		return strClientRecord;
	}
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static vector <clsBankClient> _LoadClientsDataFromFileToVector() {
		vector <clsBankClient> vClients;
		fstream file(ClientsFile, ios::in);
		if (file.is_open()) {

			string line;

			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				vClients.push_back(client);
			}
			file.close();
		}
		return vClients;
	}
	static void _LoadClientsDataFromVectorToFile(vector <clsBankClient> clients) {
		fstream file(ClientsFile, ios::out); // overwrite

		if (file.is_open()) {
			for (const clsBankClient& client : clients) {	
				if(!client._MarkedForDelete)
					file << _ConvertClientObjectToLine(client, FileSeperator) << endl;
			}
			file.close();
		}
	}
	
	static clsBankClient _GetEmptyClientObject() { return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0); }
	
	string _ConvertTransferRecordToLine(double TransferedAmount,clsBankClient RecieverCleint, string Seperator ="#//#") {
		string Line;
		Line += clsDate::GetSystemTimeAndDateString("dd/mm/yyyy ") + Seperator;
		Line += _AccountNumber + Seperator; 
		Line += RecieverCleint.AccountNumber() + Seperator;
		Line += to_string(TransferedAmount) + Seperator; 
		Line += to_string(_AccountBalance) + Seperator;
		Line += to_string(RecieverCleint.AccountBalance) + Seperator;
		Line += SystemUser.Username;
		return Line;
	}
	struct stTransferRecord;
	static stTransferRecord _ConverTransferlogLineToRecord(string line, string Seperator = "#//#") {
		stTransferRecord stTransferRecord;
		vector <string> vTransferRecord = clsString::Split(line, Seperator);
		stTransferRecord.Date_Time = vTransferRecord.at(0);
		stTransferRecord.SenderAccountNumber = vTransferRecord.at(1);
		stTransferRecord.RecieverAccountNumber = vTransferRecord.at(2);
		stTransferRecord.TrasnferedAmout = stod(vTransferRecord.at(3));
		stTransferRecord.SenderAccountBalance = stod(vTransferRecord.at(4));
		stTransferRecord.RecieverAccountBalance = stod(vTransferRecord.at(5));
		stTransferRecord.Username = vTransferRecord.at(6);
		return stTransferRecord;
	}
	
	bool _RegisterTransferRecord(double TransferedAmount, clsBankClient& RecieverClient, string Username) {
		fstream file(TransferLogFile, ios::app | ios::out);

		if (file.is_open()) {
			file << _ConvertTransferRecordToLine(TransferedAmount, RecieverClient) << endl;
			file.close();

			return true;
		}

		return false;
	}
public :
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string AccountNumber, string PinCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_AccountBalance = AccountBalance;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;
	}

	struct stTransferRecord {
		string Date_Time;
		string SenderAccountNumber;
		string RecieverAccountNumber;
		string Username;
		double TrasnferedAmout, SenderAccountBalance, RecieverAccountBalance;
	};



	string GetPinCode() { return _PinCode; }
	void SetPinCode(string PinCode) { _PinCode = PinCode; }
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	double GetAccountBalance() { return _AccountBalance; }
	void SetAccountBalance(double AccountBalance) { _AccountBalance = AccountBalance; }
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	string AccountNumber() { return _AccountNumber; }

	/*
	this method is removed because No UI related code inside object
	void Print() {
		cout << "Client Card" << endl;
		cout << "------------------------------" << endl;
		cout << "First Name      : " << FirstName << endl;
		cout << "Last Name       : " << LastName << endl;
		cout << "Email           : " << Email << endl;
		cout << "Phone Number    : " << PhoneNumber << endl;
		cout << "Account Number  : " << _AccountNumber << endl;
		cout << "PinCode         : " << _PinCode << endl;
		cout << "Account Balance : " << _AccountBalance << endl;
		cout << "------------------------------" << endl;
	}*/

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	
	enum enSaveResults {saveField_EmptyObject, saveField_AccountNumExist,saveSucceeded };
	enSaveResults Save() {
		switch (_Mode) {
		
		case EmptyMode:
			return enSaveResults::saveField_EmptyObject;
		
		case UpdateMode:
			_Update();
			return enSaveResults::saveSucceeded;
		
		case AddNewMode:
			if (clsBankClient::DoesClientExist(AccountNumber()))
				return enSaveResults::saveField_AccountNumExist;
			_Add();
			_Mode = enMode::UpdateMode;
			return enSaveResults::saveSucceeded;
	
		}
	}

	static clsBankClient Find(string AccountNumber) {

		fstream file(ClientsFile, ios::in);
		
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line, FileSeperator);
				if (client.AccountNumber() == AccountNumber)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}

		return _GetEmptyClientObject();

	}
	static clsBankClient Find(string AccountNumber, string PinCode){
		
		fstream file(ClientsFile, ios::in);

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line, FileSeperator);
				if (client.AccountNumber() == AccountNumber && client.PinCode == PinCode)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}

		return _GetEmptyClientObject();

	}
	static bool DoesClientExist(string AccountNumber) {
		clsBankClient client = Find(AccountNumber);
		return (!client.IsEmpty());
	}

	static clsBankClient GetAddClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	
	bool Delete() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToVector();
		bool IsDeleted = false;
		for (clsBankClient& client : vClients) {
			if (client.AccountNumber() == AccountNumber())
			{
				client._MarkedForDelete = true;
				IsDeleted = true;
				break;
			}
			
		}
		
		_LoadClientsDataFromVectorToFile(vClients);
		*this = _GetEmptyClientObject();
		
		return IsDeleted;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFileToVector();
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToVector();
		double TotalBalance = 0;
		for ( clsBankClient& client : vClients)
			TotalBalance += client.AccountBalance;
		return TotalBalance;

	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;
		else 
		{
			AccountBalance -= Amount;
			Save();
			return true;
		}
	}
	bool Transfer(double AmountToTransfer, clsBankClient & ReciecverClient) {
		if ((AmountToTransfer > _AccountBalance || AmountToTransfer <= 0) || AccountNumber() == ReciecverClient.AccountNumber() )
			return false;
		
		Withdraw(AmountToTransfer);
		ReciecverClient.Deposit(AmountToTransfer);
		
		_RegisterTransferRecord(AmountToTransfer, ReciecverClient, SystemUser.Username);

		return true;
	}


	static vector <stTransferRecord> GetTransferRecordsListScreen() {
		
		fstream file(TransferLogFile, ios::in);
		vector <stTransferRecord> vTransferRecords;
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				vTransferRecords.push_back(_ConverTransferlogLineToRecord(line));
			}
			file.close();
		}

		return vTransferRecords;
	}

	

};


/*
1 - we made these private functions static because we want to access it without declaring objects in the public static
methods such as find
2 - in object never do any operations related to UI
*/