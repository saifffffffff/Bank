#pragma once
#include <ctime>
#include <iostream>
#include <vector>
#include "clsString.h"
#include <string>

#pragma warning (disable : 4996)
using namespace std;

namespace Random {
	int GenerateRandomNumber(int From, int To) {

		int randNum = rand() % (To - From + 1) + From;

		return randNum;

	}
}
class clsDate {

private:
	short _day, _month;
	int _year;
public:

	clsDate() {
		long long t = time(0);
		tm* now = localtime(&t);
		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_day = now->tm_mday;
	}
	clsDate(string DateInString) {
		vector <string> vDate = clsString::Split(DateInString, "/");
		
		if (vDate.size() != 3)
			throw runtime_error("In Valid Date");

		this->day = stoi(vDate.at(0));
		this->month = stoi(vDate.at(1));
		this->year = stoi(vDate.at(2));
	}
	clsDate(short day, short month, int year) {
		this->year = year;
		this->month = month;
		this->day = day;
	}
	clsDate(short days, int year) {
		_day = 0;
		_month = 1;
		_year = year;

		this->AddDaysToDate(days);

	}

	static short DayOfWeekOrder(clsDate date) {

		short a = (14 - date.month) / 12;
		short y = date.year - a;
		short m = date.month + 12 * a - 2;
		short d = (int)(date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;

	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(*this);

	}

	static bool IsLeapYear(int year) {
		return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
	}
	bool IsLeapYear() {
		return IsLeapYear(this->_year);
	}

	static short TotalDaysFromTheBegingOfYear(clsDate date) {
		short TotalDays = 0;
		for (short m = 1; m < date.month; m++)
			TotalDays += NumberOfDaysInMonth(m, date.year);
		TotalDays += date.day;
		return TotalDays;
	}
	short TotalDaysFromTheBegingOfYear() {
		return TotalDaysFromTheBegingOfYear(*this);
	}

	static string DayName(short DayOrder) {
		string days[] = { "sunday", "monday", "tuesday", "wednesday","thursday", "friday" , "saturday" };
		return days[DayOrder];
	}
	string DayName() {
		return DayName(this->DayOfWeekOrder());
	}
	static string DayShortName(short DayOrder) {
		string days[] = { "Sun", "Mon", "Tue", "Wed","Thu", "Fri" , "Sat" };
		return days[DayOrder];
	}
	string DayShortName() {
		return DayShortName(this->day);
	}
	static string MonthShortName(short month) {
		string months[] = { "Jan", "Feb" ,"Mar" , "Apr" , "May", "Jun", "Jul", "Aug","Sep", "Oct", "Nov","Dec" };

		return months[month - 1];
	}
	string MonthShortName() {
		return MonthShortName(this->month);
	}
	//
	short GetDay() { return _day; }
	void setDay(short day) {
		if (day <= 0 || day > this->NumberOfDaysInMonth())
			throw runtime_error("invalid date");
		this->_day = day;
	}
	short GetMonth() { return _month; }
	void setMonth(short month) {
		if (month <= 0 || month > 12)
			throw runtime_error("invalid date");
		this->_month = month;
	}
	int GetYear() { return _year; }
	void setYear(int year) {
		if (year < 0)
			throw runtime_error("invalid date");
		this->_year = year;
	}

	__declspec(property(get = GetDay, put = setDay)) short day;
	__declspec(property(get = GetMonth, put = setMonth)) short month;
	__declspec(property(get = GetYear, put = setYear)) int year;

	//
	static short NumberOfDaysInYear(int year) {
		return IsLeapYear(year) ? 366 : 365;
	}
	short NumberOfDaysInYear() {
		return NumberOfDaysInYear(this->_year);
	}
	//
	static short NumberOfHoursInYear(int year) {
		return NumberOfDaysInYear(year) * 24;
	}
	short NumberOfHoursInYear() {
		return NumberOfHoursInYear(this->_year);
	}
	//
	static int NumberOfMinutesInYear(int year) {
		return NumberOfHoursInYear(year) * 60.f;
	}
	int NumberOfMinutesInYear() {
		return NumberOfMinutesInYear(this->_year);
	}
	//
	static int NumberOfSecondsInYear(int year) {
		return NumberOfMinutesInYear(year) * 60.f;
	}
	int NumberOfSecondsInYear() {
		return NumberOfSecondsInYear(this->_year);
	}
	//
	static short NumberOfDaysInMonth(short month, int year) {


		if (month > 12 || month < 1)
			return 0;
		short DaysInMonth[12] = { 31,28 ,31 ,30,31,30,31,31,30,31,30, 31 };

		return month == 2 ? (IsLeapYear(year) ? 29 : 28) : DaysInMonth[month - 1];

	}
	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(this->month, this->year);
	}
	//
	static short NumberOfHoursInMonth(short month, int year) {

		return NumberOfDaysInMonth(month, year) * 24;

	}
	short NumberOfHoursInMonth() {

		return NumberOfHoursInMonth(this->month, this->year) * 24;

	}
	//
	static int NumberOfMinutesInMonth(short month, int year) {
		return NumberOfHoursInMonth(month, year) * 60;
	}
	int NumberOfMinutesInMonth() {
		return NumberOfMinutesInMonth(this->month, this->year);
	}
	//
	static int NumberOfSecondsInMonth(short month, int year) {
		return NumberOfMinutesInMonth(month, year) * 60;
	}
	int NumberOfSecondsInMonth() {
		return NumberOfSecondsInMonth(this->month, this->year);
	}
	//
	static void PrintMonthCalender(short month, int year) {

		short FirstDay = DayOfWeekOrder({ 1, month, year });
		short NumberOfDays = NumberOfDaysInMonth(month, year);

		printf("________________%s________________\n\n", MonthShortName(month).c_str());
		printf("  sun  mon  tue  wed  thu  fri  sat\n");
		int i;
		for (i = 0; i < FirstDay; i++)
			cout << "     ";

		for (int j = 1; j <= NumberOfDays; j++) {
			printf("%5d", j);

			if (++i == 7)
			{
				cout << endl;
				i = 0;
			}
		}
		printf("\n___________________________________\n");



	}
	void PrintMonthCalender() {
		PrintMonthCalender(this->month, this->year);
	}
	static void PrintYearCalender(int year) {
		cout << "___________________________________\n\n";
		cout << "            " << year << " - calender\n";
		cout << "___________________________________\n\n";
		for (short month = 1; month <= 12; month++) {
			PrintMonthCalender(month, year);
			cout << endl;
		}
	}
	void PrintYearCalender() {
		PrintYearCalender(this->year);
	}
	//
	void FillRandomDate() {

		this->year = Random::GenerateRandomNumber(1, INT_MAX);
		this->month = Random::GenerateRandomNumber(1, 12);
		this->day = Random::GenerateRandomNumber(1, NumberOfDaysInMonth(this->month, this->year));

	}
	//
	static clsDate AddDaysToDate(short days, clsDate date) {

		int remainingDays = days + TotalDaysFromTheBegingOfYear(date);

		date.month = 1;
		short MonthDays;
		while (true) {

			MonthDays = NumberOfDaysInMonth(date.month, date.year);
			if (remainingDays < MonthDays) {

				date.day = (remainingDays == 0 ? remainingDays + 1 : remainingDays);
				break;
			}

			else {
				remainingDays -= MonthDays;
				date.month++;
				if (date.month > 12) {
					date.month = 1;
					date.year++;
				}

			}
		}
		return date;
	}
	void AddDaysToDate(short days) {
		*this = AddDaysToDate(days, *this);
	}
	//
	static clsDate GetDateFromDayOrderInWeek(short days, int year) {

		clsDate Date;

		Date.year = year;
		Date.month = 1;
		short RemainingDays = days;

		short DaysInMonth;
		while (true) {
			DaysInMonth = NumberOfDaysInMonth(Date.month, year);
			if (RemainingDays > DaysInMonth) {

				RemainingDays -= DaysInMonth;
				Date.month++;

			}
			else {
				Date.day = RemainingDays;
				break;

			}
		}

		return Date;

	}
	//
	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2) {
		return (date1.year < date2.year) ? true : ((date1.year == date2.year) ? ((date1.month < date2.month) ? true : ((date1.month == date2.month) ? ((date1.day < date2.day) ? true : false) : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate date2) {
		return IsDate1BeforeDate2(*this, date2);
	}
	//

	static bool IsDate1EqualsToDate2(clsDate date1, clsDate date2) {
		return (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
	}
	bool IsDate1EqualsToDate2(clsDate date2) {
		return IsDate1BeforeDate2(*this, date2);
	}
	//
	static bool IsDate1AfterDate2(clsDate date1, clsDate date2) {
		return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualsToDate2(date1, date2));
	}
	bool IsDate1AfterDate2(clsDate date2) {
		return IsDate1AfterDate2(*this, date2);
	}
	//

	static bool IsLastDayInMonth(clsDate date) {
		return date.day == NumberOfDaysInMonth(date.month, date.year) ? true : false;
	}
	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	//

	static void SwapDates(clsDate& date1, clsDate& date2) {
		clsDate temp = date1;
		date1 = date2;
		date2 = temp;
	}
	void SwapDates(clsDate& date2) {
		SwapDates(*this, date2);
	}

	static bool IsLastMonthInYear(clsDate date) {
		return (date.month == 12);
	}

	static bool IsEndOfWeek(clsDate date) {
		return (DayOfWeekOrder(date) == 6);
	}

	static bool IsWeekEnd(clsDate date) {
		short dayOrder = DayOfWeekOrder(date);
		return dayOrder == 5 || dayOrder == 6;
	}

	static bool IsBusinessDay(clsDate date) {
		return !IsWeekEnd(date);
	}

	static clsDate IncreaseDateByOneDay(clsDate date) {
		if (IsLastDayInMonth(date)) {
			if (IsLastMonthInYear(date)) {
				date.year++;
				date.day = 1;
				date.month = 1;
			}
			else {
				date.month++;
				date.day = 1;
			}
		}
		else {
			date.day++;
		}
		return date;
	}

	static clsDate IncreaseDateByOneWeek(clsDate date) {
		for (short i = 1; i <= 7; i++)
			date = IncreaseDateByOneDay(date);
		return date;
	}

	static clsDate IncreaseDateByOneMonth(clsDate date) {
		if (date.month == 12) {
			date.year++;
			date.month = 1;
		}
		else {
			date.month++;
		}
		short DaysInCurrentMonth = NumberOfDaysInMonth(date.month, date.year);
		if (date.day > DaysInCurrentMonth)
			date.day = DaysInCurrentMonth;
		return date;
	}

	static clsDate IncreaseDateByOneYear(clsDate date) {
		date.year++;
		return date;
	}

	static clsDate IncreaseDateByOneDecade(clsDate date) {
		date.year += 10;
		return date;
	}

	static clsDate IncreaseDateByOneCentury(clsDate date) {
		date.year += 100;
		return date;
	}

	static clsDate IncreaseDateByOneMillennium(clsDate date) {
		date.year += 1000;
		return date;
	}

	static clsDate IncreaseDateByXWeeks(int weeksToAdd, clsDate date) {
		for (int i = 0; i < weeksToAdd; i++)
			date = IncreaseDateByOneWeek(date);
		return date;
	}

	static clsDate IncreaseDateByXMonths(int MonthsToAdd, clsDate date) {
		for (int i = 0; i < MonthsToAdd; i++)
			date = IncreaseDateByOneMonth(date);
		return date;
	}

	static clsDate IncreaseDateByXYears(int yearsToAdd, clsDate date) {
		date.year += yearsToAdd;
		return date;
	}

	static clsDate IncreaseDateByXDecades(int DecadesToAdd, clsDate date) {
		date.year += (DecadesToAdd * 10);
		return date;
	}

	static clsDate DecreaseDateByOneDay(clsDate date) {
		if (date.day == 1) {
			if (date.month == 1) {
				date.month = 12;
				date.year--;
			}
			else {
				date.month--;
			}
			date.day = NumberOfDaysInMonth(date.month, date.year);
		}
		else {
			date.day--;
		}
		return date;
	}

	static clsDate DecreaseDateByOneWeek(clsDate date) {
		for (short i = 0; i < 7; i++) {
			date = DecreaseDateByOneDay(date);
		}
		return date;
	}

	static clsDate DecreaseDateByOneMonth(clsDate date) {
		if (date.month == 1) {
			date.year--;
			date.month = 12;
		}
		else {
			date.month--;
		}
		short MonthDays = NumberOfDaysInMonth(date.month, date.year);
		if (date.day > MonthDays)
			date.day = MonthDays;
		return date;
	}

	static clsDate DecreaseDateByOneYear(clsDate date) {
		date.year--;
		return date;
	}

	static clsDate DecreaseDateByOneDecade(clsDate date) {
		date.year -= 10;
		return date;
	}

	static clsDate DecreaseDateByOneCentury(clsDate date) {
		date.year -= 100;
		return date;
	}

	static clsDate DecreaseDateByOneMillennium(clsDate date) {
		date.year -= 1000;
		return date;
	}

	static clsDate DecreaseDateByXDays(int DaysToDecrease, clsDate date) {
		for (int i = 0; i < DaysToDecrease; i++)
			date = DecreaseDateByOneDay(date);
		return date;
	}

	static clsDate DecreaseDateByXWeeks(int WeeksToDecrease, clsDate date) {
		for (int i = 0; i < WeeksToDecrease; i++)
			date = DecreaseDateByOneWeek(date);
		return date;
	}

	static clsDate DecreaseDateByXMonths(int MonthsToDecrease, clsDate date) {
		for (int i = 0; i < MonthsToDecrease; i++)
			date = DecreaseDateByOneMonth(date);
		return date;
	}

	static clsDate DecreaseDateByXYears(int YearsToDecrease, clsDate date) {
		date.year += YearsToDecrease;
		return date;
	}

	static clsDate DecreaseDateByXDecades(int DecadesToDecrease, clsDate date) {
		date.year += (10 * DecadesToDecrease);
		return date;
	}

	static int GetDifferenceInDays(clsDate date1, clsDate date2, bool IncludeEndDay = false) {
		int days = 0;
		if (!IsDate1BeforeDate2(date1, date2)) {
			SwapDates(date1, date2);

		}

		while (IsDate1BeforeDate2(date1, date2)) {
			days++;
			date1 = IncreaseDateByOneDay(date1);
		}

		return IncludeEndDay ? ++days : days;
	}

	static short DaysUntilEndOfWeek(clsDate date) {
		return 6 - DayOfWeekOrder(date);
	}

	static short DaysUntilEndOfMonth(clsDate date) {
		clsDate EndOfMonthDate(NumberOfDaysInMonth(date.month, date.year), date.month, date.year);
		return GetDifferenceInDays(EndOfMonthDate, date, false);
	}

	static short DaysUntilEndOfYear(clsDate date) {
		clsDate EndOfYearDate(31, 12, date.year);
		return GetDifferenceInDays(EndOfYearDate, date, true);
	}

	static void PrintDateAndDay(clsDate date) {
		string day = DayName(DayOfWeekOrder(date));
		cout << "Today is " << day << " , " << date.day << "/" << date.month << "/" << date.year << endl;
	}

	static int CountVacationDays(clsDate DateFrom, clsDate DateTo) {
		int VacatoinDaysCount = 0;
		while (!IsDate1EqualsToDate2(DateFrom, DateTo)) {
			if (IsBusinessDay(DateFrom))
				VacatoinDaysCount++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return VacatoinDaysCount;
	}

	static clsDate CalculateReturnDate(clsDate DateFrom, int VacationDays) {
		int WeekEndsCounter = 0;

		for (int i = 1; i <= VacationDays + WeekEndsCounter; i++) {
			if (IsWeekEnd(DateFrom))
				WeekEndsCounter++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	static bool IsValidDate(clsDate date) {
		return (date.year > 0) && (date.day > 0) && (date.day <= NumberOfDaysInMonth(date.month, date.year));
	}

	static clsDate StringToDate(string DateInString) {
		vector<string> vDate = clsString::Split(DateInString, "/");

		if (vDate.size() != 3)
			return clsDate();

		return clsDate(stoi(vDate.at(0)), stoi(vDate.at(1)), stoi(vDate.at(2)));
	}

	static string DateToString(clsDate Date) {
		return to_string(Date.day) + '/' + to_string(Date.month) + '/' + to_string(Date.year);
	}

	static string FormatDate(clsDate date, string FormatDate = "dd/mm/yyyy") {
		FormatDate = clsString::ReplaceWord(FormatDate, "dd", to_string(date.day));
		FormatDate = clsString::ReplaceWord(FormatDate, "mm", to_string(date.month));
		FormatDate = clsString::ReplaceWord(FormatDate, "yyyy", to_string(date.year));
		
		return FormatDate;
	}

	static string GetSystemTimeString(string FormatTime = "hh:mm:ss") {
		
		time_t t = time(0);
		tm* now = localtime(&t);

		FormatTime = clsString::ReplaceWord(FormatTime, "hh", to_string(now->tm_hour));
		FormatTime = clsString::ReplaceWord(FormatTime, "mm", to_string(now->tm_min));
		FormatTime = clsString::ReplaceWord(FormatTime, "ss", to_string(now->tm_sec));

		return FormatTime;

	}

	static string GetSystemTimeAndDateString(string sFormatDate = "dd/mm/yyyy", string sFormatTime = "hh:mm:ss") {
		return FormatDate(clsDate(), sFormatDate) + GetSystemTimeString(sFormatTime);
	}

	// Instance methods
	bool IsLastMonthInYear() { return IsLastMonthInYear(*this); }
	bool IsEndOfWeek() { return IsEndOfWeek(*this); }
	bool IsWeekEnd() { return IsWeekEnd(*this); }
	bool IsBusinessDay() { return IsBusinessDay(*this); }

	void IncreaseDateByOneDay() { *this = IncreaseDateByOneDay(*this); }
	void IncreaseDateByOneWeek() { *this = IncreaseDateByOneWeek(*this); }
	void IncreaseDateByOneMonth() { *this = IncreaseDateByOneMonth(*this); }
	void IncreaseDateByOneYear() { *this = IncreaseDateByOneYear(*this); }
	void IncreaseDateByOneDecade() { *this = IncreaseDateByOneDecade(*this); }
	void IncreaseDateByOneCentury() { *this = IncreaseDateByOneCentury(*this); }
	void IncreaseDateByOneMillennium() { *this = IncreaseDateByOneMillennium(*this); }

	void IncreaseDateByXWeeks(int weeksToAdd) { *this = IncreaseDateByXWeeks(weeksToAdd, *this); }
	void IncreaseDateByXMonths(int MonthsToAdd) { *this = IncreaseDateByXMonths(MonthsToAdd, *this); }
	void IncreaseDateByXYears(int yearsToAdd) { *this = IncreaseDateByXYears(yearsToAdd, *this); }
	void IncreaseDateByXDecades(int DecadesToAdd) { *this = IncreaseDateByXDecades(DecadesToAdd, *this); }

	void DecreaseDateByOneDay() { *this = DecreaseDateByOneDay(*this); }
	void DecreaseDateByOneWeek() { *this = DecreaseDateByOneWeek(*this); }
	void DecreaseDateByOneMonth() { *this = DecreaseDateByOneMonth(*this); }
	void DecreaseDateByOneYear() { *this = DecreaseDateByOneYear(*this); }
	void DecreaseDateByOneDecade() { *this = DecreaseDateByOneDecade(*this); }
	void DecreaseDateByOneCentury() { *this = DecreaseDateByOneCentury(*this); }
	void DecreaseDateByOneMillennium() { *this = DecreaseDateByOneMillennium(*this); }

	void DecreaseDateByXDays(int DaysToDecrease) { *this = DecreaseDateByXDays(DaysToDecrease, *this); }
	void DecreaseDateByXWeeks(int WeeksToDecrease) { *this = DecreaseDateByXWeeks(WeeksToDecrease, *this); }
	void DecreaseDateByXMonths(int MonthsToDecrease) { *this = DecreaseDateByXMonths(MonthsToDecrease, *this); }
	void DecreaseDateByXYears(int YearsToDecrease) { *this = DecreaseDateByXYears(YearsToDecrease, *this); }
	void DecreaseDateByXDecades(int DecadesToDecrease) { *this = DecreaseDateByXDecades(DecadesToDecrease, *this); }

	short DaysUntilEndOfWeek() { return DaysUntilEndOfWeek(*this); }
	short DaysUntilEndOfMonth() { return DaysUntilEndOfMonth(*this); }
	short DaysUntilEndOfYear() { return DaysUntilEndOfYear(*this); }

	void PrintDateAndDay() { PrintDateAndDay(*this); }
	string ToString() { return DateToString(*this); }
	string Format(string format = "dd/mm/yyyy") { return FormatDate(*this, format); }

	enum enDateCompare { Before = -1, Equal, After };
	static enDateCompare CompareDate(clsDate date1, clsDate date2) {
		// Before -1
		// equal 0
		// after 1

		if (IsDate1BeforeDate2(date1, date2))
			return Before;
		if (IsDate1EqualsToDate2(date1, date2))
			return Equal;

		return After;

	}
	enDateCompare CompareDate(clsDate date2) {
		return CompareDate(*this, date2);
	}
};


