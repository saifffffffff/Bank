#pragma once
#include "clsDate.h"


class clsPeriod {
public:
	clsDate StartDate;
	clsDate EndDate;

	clsPeriod(clsDate StartDate, clsDate EndDate) {
		if (!clsDate::IsDate1BeforeDate2(StartDate, EndDate)) {
			clsDate::SwapDates(StartDate, EndDate);
		}
		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}

	void setStartDay(short day, short month, int year) {
		StartDate.day = day;
		StartDate.month = month;
		StartDate.year = year;
	}

	void setEndDay(short day, short month, int year) {
		EndDate.day = day;
		EndDate.month = month;
		EndDate.year = year;
	}



	static void SwapPeriods(clsPeriod& period1, clsPeriod& period2) {
		clsPeriod temp = period1;
		period1 = period2;
		period2 = temp;

	}
	void SwapPeriods(clsPeriod& period2) {
		SwapPeriods(*this, period2);
	}

	static bool IsOverlapPeriods(clsPeriod period1, clsPeriod period2) {

		return !(clsDate::CompareDate(period1.StartDate, period2.EndDate) == clsDate::After || clsDate::CompareDate(period1.EndDate, period2.StartDate) == clsDate::Before);

	}
	bool IsOverlapPeriods(clsPeriod period2) {
		return IsOverlapPeriods(*this, period2);
	}

	static int CalculatePeriodLenght(clsPeriod period, bool IncludeEndDay = false) {
		return clsDate::GetDifferenceInDays(period.StartDate, period.EndDate, IncludeEndDay);
	}
	int CalculatePeriodLenght(bool IncludeEndDay = false) {
		return CalculatePeriodLenght(*this, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsPeriod period, clsDate date) {
		return !(
			clsDate::CompareDate(period.StartDate, date) == clsDate::After
			||
			clsDate::CompareDate(period.EndDate, date) == clsDate::Before
			);
	}
	bool IsDateWithinPeriod(clsDate date) {
		return IsDateWithinPeriod(*this, date);
	}

	static int CountOverlapDays(clsPeriod period1, clsPeriod period2) {

		if (!IsOverlapPeriods(period1, period2))
			return 0;

		int overlapDays = 0;

		if (CalculatePeriodLenght(period1) < CalculatePeriodLenght(period2))
			SwapPeriods(period1, period2);

		if (IsDateWithinPeriod(period1, period2.StartDate) && IsDateWithinPeriod(period1, period2.EndDate))
			overlapDays = CalculatePeriodLenght(period2);

		else if (IsDateWithinPeriod(period1, period2.StartDate))
			overlapDays = CalculatePeriodLenght({ period2.StartDate, period1.EndDate });

		else if (IsDateWithinPeriod(period2, period1.StartDate))
			overlapDays = CalculatePeriodLenght({ period1.StartDate, period2.EndDate });

		return overlapDays + 1;

	}
	int CountOverlapDays(clsPeriod period2) {
		return CountOverlapDays(*this, period2);
	}
};

