#pragma once
#include <random>
#include <string>
#include <iostream>
using namespace std;

class clsUtil
{
public:
	enum enCharType { CapitalLetter, SmallLetter, SpecialChar, Digit, MixChar };
	static void Srand() {
		srand(time(0));
	}
	static int GenerateRandomNumber(int From, int To) {

		int randNum = rand() % (To - From + 1) + From;

		return randNum;

	}
	static char GetRandomCharacter(enCharType charType = MixChar) {
		
		if (charType == MixChar)
			charType = (enCharType)GenerateRandomNumber(0, 3);

		switch (charType)
		{
		case CapitalLetter:
			return char(GenerateRandomNumber(65, 90));

		case SmallLetter:
			return char(GenerateRandomNumber(97, 122));

		case SpecialChar:
			return char(GenerateRandomNumber(33, 47));

		case Digit:
			return char(GenerateRandomNumber(48, 57));

		default:
			break;
		}
	}
	static string GenerateWord(short len, enCharType charType) {
		string word = "";

		for (short i = 0; i < len; i++)
			word += GetRandomCharacter(charType);
		return word;
	}
	static 	string GenerateKey() {
		string key = "";
		key = key + GenerateWord(4, CapitalLetter) + '-';
		key = key + GenerateWord(4, CapitalLetter) + '-';
		key = key + GenerateWord(4, CapitalLetter) + '-';
		key = key + GenerateWord(4, CapitalLetter);
		return key;

	}
	static void GenerateKeys(string keys[], int numberOfKeys) {
		for (int i = 0; i < numberOfKeys; i++) {
			keys[i] = GenerateKey();
		}
	}

	static void Swap(int& A, int& B) {


		int temp = A;
		A = B;
		B = temp;

	}
	static void Swap(short& A, short& B) {


		short temp = A;
		A = B;
		B = temp;

	}
	static void Swap(double& A, double& B) {


		double temp = A;
		A = B;
		B = temp;

	}
	static void Swap(float& A, float& B) {


		float temp = A;
		A = B;
		B = temp;

	}
	static void Swap(string& A, string& B) {


		string temp = A;
		A = B;
		B = temp;

	}

	static string RepeatString(short RepititionTimes, string StringToRepeat) {
		string Line = "";
		for (short i = 0; i < RepititionTimes; i++)
			Line += StringToRepeat;
		return Line;
	}

	static 	void ShuffleArray(int arr[], int size) {

		for (int i = 0; i < size; i++) {
			Swap(arr[GenerateRandomNumber(0, size - 1)], arr[GenerateRandomNumber(0, size - 1)]);
		}

	}
	static 	void ShuffleArray(double arr[], int size) {

		for (int i = 0; i < size; i++) {
			Swap(arr[GenerateRandomNumber(0, size - 1)], arr[GenerateRandomNumber(0, size - 1)]);
		}

	}
	static 	void ShuffleArray(string arr[], int size) {

		for (int i = 0; i < size; i++) {
			Swap(arr[GenerateRandomNumber(0, size - 1)], arr[GenerateRandomNumber(0, size - 1)]);
		}

	}
	static 	void ShuffleArray(float arr[], int size) {

		for (int i = 0; i < size; i++) {
			Swap(arr[GenerateRandomNumber(0, size - 1)], arr[GenerateRandomNumber(0, size - 1)]);
		}

	}

	static	void FillArrayWithRandomNumbers(int arr[], int size,int from = -100, int to = 100 ) {
		for (int i = 0; i < size; i++)
			arr[i] = GenerateRandomNumber(from, to);
	}
	static void FillArrayWithRandomWords(string arr[], int size, int lenOfWords, enCharType charType = enCharType::MixChar){
		for (int i = 0; i < size; i++)
			arr[i] = GenerateWord(lenOfWords, charType);
	}
	static string  EncryptText(string Text, short EncryptionKey = -2)
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] + EncryptionKey);

		}

		return Text;

	}
	static string  DecryptText(string Text, short EncryptionKey = -2)
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] - EncryptionKey);

		}
		return Text;

	}

	static string DigitToString(long long Number) {


		if (Number == 0)
			return "";

		if (Number <= 10) {
			string NumbersFrom1To10[] = { "","one" , "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
			return NumbersFrom1To10[Number];
		}

		else if (Number >= 11 && Number <= 19) {
			string NumbersFrom11To19[] = { "eleven" ,"twelve", "thirteen", "forteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
			return NumbersFrom11To19[Number - 11];
		}

		else if (Number >= 20 && Number <= 99) {
			string DecadesNumbers[] = { "","ten" ,"tweny" , "thirty", "fourty" , "fifty", "sixty" , "seventy" , "eighy", "ninety" };

			return DecadesNumbers[(Number / 10)] + " " + DigitToString(Number % 10);
		}

		else if (Number >= 100 && Number <= 999) {

			if (Number < 200)
				return  "one hundred " + DigitToString(Number % 100);
			else
				return DigitToString(Number / 100) + " hundreds " + DigitToString(Number % 100);

		}

		else if (Number >= 1000 && Number < 999999) {

			if (Number < 2000)
				return "one thousand " + DigitToString(Number % 1000);
			else
				return DigitToString(Number / 1000) + " thousands " + DigitToString(Number % 1000);

		}


		else if (Number >= 1000000 && Number < 999999999) {

			if (Number < 2000000)
				return "one million " + DigitToString(Number % 1000000);
			else
				return DigitToString(Number / 1000000) + " million " + DigitToString(Number % 1000000);
		}


		else if (Number >= 1000000000 && Number < 10000000000000) {
			int RightNineNumbers = Number % 1000000000;
			short LeftThreeNumbers = Number / 1000000000;
			if (Number < 2000000000)
				return "one billion " + DigitToString(Number % 1000000000);
			else
				return DigitToString(Number / 1000000000) + " billion " + DigitToString(Number % 1000000000);

		}


	}

};

