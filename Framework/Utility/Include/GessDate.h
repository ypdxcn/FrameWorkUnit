#ifndef _GESS_DATE_H_
#define _GESS_DATE_H_

#include "strutils.h"
#include "Gess.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace strutils;

typedef enum
{
	E_YEAR_LEAP_NON,
	E_YEAR_LEAP
} EnumYearLeap;

class istream;
class ostream;
class UTIL_CLASS CGessDate
{
	friend std::ostream& operator<<(std::ostream&, const CGessDate&);
	friend std::istream& operator >> (std::istream&, CGessDate&);
	friend class CGessDateTime;
public:
	CGessDate();
	CGessDate(int y, int m, int d);
	CGessDate(const string& sDate, const string& sSeprator = "-");
	CGessDate(const CGessDate& oDate);
	CGessDate(int nDate);

	inline int Month() const { return m_nMonth; }
	inline int Day() const { return m_nDay; }
	inline int Year() const { return m_nYear; }
	inline int WeekDay() const { return m_nWeekDay; }
	inline int IntergerFormat() const { return m_nYear * 10000 + m_nMonth * 100 + m_nDay; }

	static int ThisYear();
	static int ThisMonth();
	static int ThisDay();
	static int ThisWeekDay();
	static int WeekDay(int y, int m, int d);
	static int ThisIntergerFormat();

	static CGessDate InitialDate();
	void ToInitialVal();

	int IntervalToToday();
	bool IsToday();
	void Day2Today();
	bool FromString(const string & sDate, const string& sSeprator = "-");
	string ToString(const string& sSeprator = "");
	static string ToString(time_t t, const string& sSeprator = "");
	static string NowToString(const string& sSeprator = "-");

	CGessDate& operator++(int);
	CGessDate& operator--(int);
	CGessDate& operator+=(int);
	CGessDate& operator-=(int);
	CGessDate operator+(int nDays) const;
	CGessDate operator-(int nDays) const;
	int operator-(const CGessDate& d2) const;
	CGessDate& operator-();

	int Compare(const CGessDate&) const;
	int CompareNow() const;
	bool operator<(const CGessDate& d2) const { return Compare(d2) < 0; }
	bool operator<=(const CGessDate& d2) const { return Compare(d2) <= 0; }
	bool operator>(const CGessDate& d2) const { return Compare(d2) > 0; }
	bool operator>=(const CGessDate& d2) const { return Compare(d2) >= 0; }
	bool operator==(const CGessDate& d2) const { return Compare(d2) == 0; }
	bool operator!=(const CGessDate& d2) const { return Compare(d2) != 0; }

	static EnumYearLeap IsLeap(int y);

private:
	int m_nMonth;
	int m_nDay;
	int m_nYear;
	int m_nWeekDay;

	static int m_nDayTab[2][13];
};
#endif