#pragma once
#include <iostream>

using namespace std;


class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _PhoneNumber;
public:

	
	clsPerson(string FirstName, string LastName, string Email, string PhoneNumber) {
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_PhoneNumber = PhoneNumber;
	}

	string GetFirstName() { return _FirstName; }
	void SetFirstName(string FirstName) { _FirstName = FirstName; }
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;


	string GetLastName() { return _LastName; }
	void SetLastName(string LastName) { _LastName = LastName; }
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	string GetEmail() { return _Email; }
	void SetEmail(string Email) { _Email = Email; }
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;


	string GetPhoneNumber() { return _PhoneNumber; }
	void SetPhoneNumber(string PhoneNumber) { _PhoneNumber = PhoneNumber; }
	__declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) string PhoneNumber;


	string FullName() {
		return _FirstName + " " + _LastName;
	}
};

