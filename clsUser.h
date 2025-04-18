#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "GlobalFiles.h"


class clsUser : public clsPerson
{	
private:
	

	enum enMode { Update, Add , Empty};
	enMode _Mode;

	string _Username;
	string _Password;
	short _Permissions;
	bool _MarkedForDelete = false;

	void _Add() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this, "#//#"));
	}
	void _Update() {
		vector <clsUser> vUsers = _LoadUsersDataFromFileToVector();
		for (clsUser& user : vUsers) {
			if (user.Username == _Username)
				user = *this;
		}

		_LoadUsersDataFromVectorToFile(vUsers);
	}
	static void _AddDataLineToFile(string DataLine) {
		fstream file(UsersFile, ios::app | ios::out);
		if (file.is_open())
		{
			file << DataLine << endl;
			file.close();
		}
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {
		string strUserRecord = "";
		strUserRecord += User.FirstName + Seperator;
		strUserRecord += User.LastName + Seperator;
		strUserRecord += User.Email + Seperator;
		strUserRecord += User.PhoneNumber + Seperator;
		strUserRecord += User.Username + Seperator;
		strUserRecord += clsUtil::EncryptText(User.Password,-2) + Seperator;
		strUserRecord += to_string(User.Permissions);

		return strUserRecord;
	}
	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::Update, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5],-2), stoi(vUserData[6]));

	}

	static vector <clsUser> _LoadUsersDataFromFileToVector() {
		vector <clsUser> vUsers;
		fstream file(UsersFile, ios::in);
		if (file.is_open()) {

			string line;

			while (getline(file, line)) {
				if(!line.empty())
				{
					clsUser user = _ConvertLineToUserObject(line, FileSeperator);
					vUsers.push_back(user);
				}
			}
			file.close();
		}
		return vUsers;
	}
	static void _LoadUsersDataFromVectorToFile(vector <clsUser> vUsers) {
		fstream file(UsersFile , ios::out); // overwrite

		if (file.is_open()) {
			for (const clsUser& user : vUsers) {
				if (!user._MarkedForDelete)
					file << _ConvertUserObjectToLine(user, "#//#") << endl;
			}
			file.close();
		}
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::Empty, "","","","","","",0);
	}

	string _PrepareRegisterRecord(string Seperator = "#//#") {
		string RegisterRecordLine;
		RegisterRecordLine += clsDate::GetSystemTimeAndDateString("dd/mm/yyyy - ") + Seperator;
		RegisterRecordLine += _Username + Seperator;
		RegisterRecordLine += clsUtil::EncryptText(_Password) + Seperator;
		RegisterRecordLine += to_string(_Permissions);
		return RegisterRecordLine;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToStruct(string line) {
		vector <string> vLoginRegisterDataLine = clsString::Split(line, "#//#");
		stLoginRegisterRecord LoginRegisterRecord;
		LoginRegisterRecord.Date_Time = vLoginRegisterDataLine.at(0);
		LoginRegisterRecord.Username = vLoginRegisterDataLine.at(1);
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterDataLine.at(2));
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterDataLine.at(3));

		return LoginRegisterRecord;
	}
	
public:


	clsUser(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string UserName, string Password, short Permissions) 
		: clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_Permissions = Permissions;
		_Password = Password;
		_Username = UserName;
	}

	struct stLoginRegisterRecord {
		string Date_Time;
		string Username;
		string Password;
		short Permissions;
	};

	string GetUserName() { return _Username; }
	void SetUserName(string username) { _Username = username; }
	__declspec(property(get = GetUserName, put = SetUserName)) string Username;

	short GetPermissions() { return _Permissions; }
	void SetPermissions(short permissions) { _Permissions = permissions; }
	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

	string GetPassword() { return _Password; }
	void SetPassword(string password) { _Password = password; }
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	enum enPermissions {pAll= -1,pShowClientList = 1,pAddNewClient = 2,pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16 , pTransactions = 32, pManageUsers = 64,pShowLoginRegister = 128 };

	bool IsEmpty() {
		return (_Mode == Empty);
	}

	static clsUser Find(string username) {
		vector <clsUser> vUsers = _LoadUsersDataFromFileToVector();
		for (clsUser& User : vUsers)
			if (User.Username == username)
				return User;

		return _GetEmptyUserObject();

	}
	static clsUser Find(string username, string password) {
		vector <clsUser> vUsers = _LoadUsersDataFromFileToVector();
		for (clsUser& User : vUsers)
			if (User.Username == username && User.Password == password)
				return User;

		return _GetEmptyUserObject();

	}
	static bool DoesUserExist(string username) {
		clsUser user = Find(username);
		return !user.IsEmpty();
	}
	
	static vector <clsUser> GetUsersList() {
		return _LoadUsersDataFromFileToVector();
	}

	bool Delete() {
		
		vector <clsUser> vUsers = _LoadUsersDataFromFileToVector();
		bool IsDeleted = false;
		for (clsUser& user : vUsers)
			if (user.Username == _Username)
			{
				IsDeleted = true;
				user._MarkedForDelete = true;
			}

		_LoadUsersDataFromVectorToFile(vUsers);
		*this = _GetEmptyUserObject();
		return IsDeleted;
	}
	
	static clsUser GetAddUserObject(string UserName) { 
		return clsUser(Add, "", "", "", "", UserName, "", 0);
	}

	enum enSaveResult {SavedSuccessfuly, SavedField_EmptyObj, SaveField_UserExists};
	enSaveResult Save() {
		switch (_Mode) {
		
		case enMode::Empty :
			return enSaveResult::SavedField_EmptyObj;
		
		case enMode::Update:
			_Update();
			break;
		case enMode::Add:
			
			if (DoesUserExist(_Username))
			{
				return enSaveResult::SaveField_UserExists;
			}
			else {
				_Add();
				_Mode = Update;
				return enSaveResult::SavedSuccessfuly;
			}
		
		}
	}

	bool CheckPermission(enPermissions permission) {
		if (this->Permissions == enPermissions::pAll) return true;
		if ((this->Permissions & permission) == permission) return true;
		return false;
	}

	void RegisterLogin() {
		fstream file("LoginRegister.txt", ios::app | ios::out);
		
		if (file.is_open()) {
			file << _PrepareRegisterRecord(FileSeperator) << endl;
			file.close();
		}

	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {
		
		fstream file("LoginRegister.txt", ios::in);

		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToStruct(line));
			}
			file.close();
		}

		return vLoginRegisterRecord;


	}
	
};

