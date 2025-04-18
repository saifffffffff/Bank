#pragma once
#include <string>
#include <iostream>
#include "clsString.h"
using namespace std;

class clsInputValidate
{
public:
	static bool IsNumberBetween(int num,int From, int To) {
		return (num >= From ) && (num <= To);
	}
	static double ReadDoubleInRange(double From, double To, string message, string OutOfRangeMessage = "", string InvalidInputMessage = "") {
		double num;
		cout << message;
		cin >> num;
		while (num > To || num < From || cin.fail()) {

			if (cin.fail())
				cout << InvalidInputMessage;
			else
				cout << OutOfRangeMessage;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}
	static int ReadIntInRange(int From, int To, string message, string OutOfRangeMessage = "", string InvalidInputMessage = "") {
		int num;
		cout << message;
		cin >> num;
		while (num > To || num < From || cin.fail()) {

			if (cin.fail())
				cout << InvalidInputMessage;
			else
				cout << OutOfRangeMessage;

			cin.clear();

			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}
	static float ReadFloatInRange(float From, float To, string message, string OutOfRangeMessage = "", string InvalidInputMessage = "") {
		float num;
		cout << message;
		cin >> num;
		while (num > To || num < From || cin.fail()) {

			if (cin.fail())
				cout << InvalidInputMessage;
			else
				cout << OutOfRangeMessage;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}

	static int ReadInt(string message, string AlertMessage = "") {
		int num;
		cout << message;
		cin >> num;
		while (cin.fail()) {
			cin.clear();
			cout << AlertMessage;
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}
	static double ReadDouble(string message, string AlertMessage = "") {
		double num;
		cout << message;
		cin >> num;
		while (cin.fail()) {
			cin.clear();
			cout << AlertMessage;
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}
	static float ReadFloat(string message, string AlertMessage = "") {
		float num;
		cout << message;
		cin >> num;
		while (cin.fail()) {
			cin.clear();
			cout << AlertMessage;
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		return num;
	}

	static string ReadString(string message) {
		string str = "";

		while (str.empty()) {
			cout << message;
			// ws removes the spaces / tabs / new lines from the input
			getline(cin >> ws, str);
		}

		return clsString::Trim(str);
	}
	static char ReadChar(string message) {
		char c;
		string input = "";
		while (true) {
			cout << message;
			getline(cin >> ws, input);
			if (input.length() == 1) {
				c = input[0];
				break;
			}
		}
		return c;
	}

};

