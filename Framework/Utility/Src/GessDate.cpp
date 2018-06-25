#include <iostream>
#include <time.h>
#include <assert.h>
#include "GessDate.h"

int CGessDate::m_nDayTab[2][13] =
{
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

std::ostream& operator<<(std::ostream& os, const CGessDate& d)
{
	os << d.m_nYear << '-' << d.m_nMonth << '-' << d.m_nDay;
	return os;
}

std::istream& operator >> (std::istream& is, CGessDate& d)
{
	char slash;
	is >> d.m_nYear >> slash >> d.m_nMonth >> slash >> d.m_nDay;
	return is;
}

CGessDate::CGessDate()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	m_nMonth = stTime->tm_mon + 1;
	m_nDay = stTime->tm_mday;
	m_nYear = stTime->tm_year + 1900;
	m_nWeekDay = stTime->tm_wday;
}

CGessDate::CGessDate(int y, int m, int d)
{
	bool blValid = true;
	if (y < 1900 || m > 12 || m <= 0 || d <= 0)
	{
		blValid = false;
	}
	else
	{
		if (d > m_nDayTab[IsLeap(y)][m])
		{
			blValid = false;
		}
	}

	if (!blValid)
	{
		time_t tmNow;
		time(&tmNow);

		struct tm* stTime = localtime(&tmNow);


		m_nMonth = stTime->tm_mon + 1;
		m_nDay = stTime->tm_mday;
		m_nYear = stTime->tm_year + 1900;
		m_nWeekDay = stTime->tm_wday;
	}
	else
	{
		m_nMonth = m;
		m_nDay = d;
		m_nYear = y;
		m_nWeekDay = WeekDay(m_nYear, m_nMonth, m_nDay);
	}
}

CGessDate::CGessDate(int nDate)
{
	int y = nDate / 10000;
	int m = (nDate % 10000) / 100;
	int d = nDate % 100;

	//CGessDate(y,m,d);
	bool blValid = true;
	if (y < 1900 || m > 12 || m <= 0 || d <= 0)
	{
		blValid = false;
	}
	else
	{
		if (d > m_nDayTab[IsLeap(y)][m])
		{
			blValid = false;
		}
	}

	if (!blValid)
	{
		time_t tmNow;
		time(&tmNow);
		//struct tm  stTime;
		//localtime_r(&tmNow,&stTime);
		struct tm* stTime = localtime(&tmNow);

		m_nMonth = stTime->tm_mon + 1;
		m_nDay = stTime->tm_mday;
		m_nYear = stTime->tm_year + 1900;
		m_nWeekDay = stTime->tm_wday;
	}
	else
	{
		m_nMonth = m;
		m_nDay = d;
		m_nYear = y;
		m_nWeekDay = WeekDay(m_nYear, m_nMonth, m_nDay);
	}
}

CGessDate::CGessDate(const string& sDate, const string& sSeprator)
{
	bool blValid = true;
	int y, m, d;
	string sTmp = trim(sDate);

	size_t iPos = string::npos;
	if (0 != sSeprator.length())
	{
		iPos = sDate.find(sSeprator.at(0), 0);
	}

	if (string::npos != iPos)
	{
		vector<string> vTime = strutils::explodeQuoted(sSeprator, sTmp);
		size_t nSize = vTime.size();
		if (3 == nSize)
		{
			y = strutils::FromString<int>(vTime[0]);
			m = strutils::FromString<int>(vTime[1]);
			d = strutils::FromString<int>(vTime[2]);

			if (y < 1900 || m < 0 || m > 12 || d < 0 || d > 31)
			{
				blValid = false;
			}
			else if (m == 2 && d > 29)
			{
				blValid = false;
			}
			else if (m == 2 && d == 29 && E_YEAR_LEAP != IsLeap(y))
			{
				blValid = false;
			}
		}
		else
		{
			blValid = false;
		}
	}
	else
	{
		size_t nLen = sTmp.length();
		if (nLen != 8)
		{
			blValid = false;
		}
		else
		{
			y = strutils::FromString<int>(sTmp.substr(0, 4));
			m = strutils::FromString<int>(sTmp.substr(4, 2));
			d = strutils::FromString<int>(sTmp.substr(6, 2));

			if (y < 1900 || m < 0 || m > 12 || d < 0 || d > 31)
			{
				blValid = false;
			}
			else if (m == 2 && d > 29)
			{
				blValid = false;
			}
			else if (m == 2 && d == 29 && E_YEAR_LEAP != IsLeap(y))
			{
				blValid = false;
			}
		}
	}

	if (!blValid)
	{
		m_nMonth = 1;
		m_nDay = 1;
		m_nYear = 1900;
		m_nWeekDay = WeekDay(m_nYear, m_nMonth, m_nDay);
	}
	else
	{
		m_nMonth = m;
		m_nDay = d;
		m_nYear = y;
		m_nWeekDay = WeekDay(m_nYear, m_nMonth, m_nDay);
	}
}

CGessDate::CGessDate(const CGessDate& oDate)
{
	m_nMonth = oDate.m_nMonth;
	m_nDay = oDate.m_nDay;
	m_nYear = oDate.m_nYear;
	m_nWeekDay = oDate.m_nWeekDay;
}

bool CGessDate::FromString(const string & sDate, const string& sSeprator)
{
	bool blValid = true;
	int y, m, d;
	string sTmp = trim(sDate);

	size_t iPos = string::npos;
	if (0 != sSeprator.length())
	{
		iPos = sDate.find(sSeprator.at(0), 0);
	}
	if (string::npos != iPos)
	{
		vector<string> vTime = strutils::explodeQuoted(sSeprator, sTmp);
		size_t nSize = vTime.size();
		if (3 == nSize)
		{
			y = strutils::FromString<int>(vTime[0]);
			m = strutils::FromString<int>(vTime[1]);
			d = strutils::FromString<int>(vTime[2]);

			if (y < 1900 || m < 0 || m > 12 || d < 0 || d > 31)
			{
				blValid = false;
			}
			else if (m == 2 && d > 29)
			{
				blValid = false;
			}
			else if (m == 2 && d == 29 && E_YEAR_LEAP != IsLeap(y))
			{
				blValid = false;
			}
		}
		else
		{
			blValid = false;
		}
	}
	else
	{
		size_t nLen = sTmp.length();
		if (nLen != 8)
		{
			blValid = false;
		}
		else
		{
			y = strutils::FromString<int>(sTmp.substr(0, 4));
			m = strutils::FromString<int>(sTmp.substr(4, 2));
			d = strutils::FromString<int>(sTmp.substr(6, 2));

			if (y < 1900 || m < 0 || m > 12 || d < 0 || d > 31)
			{
				blValid = false;
			}
			else if (m == 2 && d > 29)
			{
				blValid = false;
			}
			else if (m == 2 && d == 29 && E_YEAR_LEAP != IsLeap(y))
			{
				blValid = false;
			}
		}
	}

	if (blValid)
	{
		m_nYear = y;
		m_nMonth = m;
		m_nDay = d;
		m_nWeekDay = WeekDay(m_nYear, m_nMonth, m_nDay);
	}
	return blValid;
}

int CGessDate::operator-(const CGessDate& d2) const
{
	int nDaysDiff = 0;
	if (*this == d2)
		return 0;

	if (*this > d2)
	{
		CGessDate oDate = d2;
		do
		{
			nDaysDiff++;
			oDate++;
		} while (oDate != *this);
		return nDaysDiff;
	}
	else
	{
		CGessDate oDate = *this;
		do
		{
			nDaysDiff++;
			oDate++;
		} while (oDate != d2);
		return -nDaysDiff;
	}
}

int CGessDate::Compare(const CGessDate& d2) const
{
	int nMonths, nDays, nYears;

	nYears = m_nYear - d2.m_nYear;
	nMonths = m_nMonth - d2.m_nMonth;
	nDays = m_nDay - d2.m_nDay;

	if (nYears == 0 && nMonths == 0 && nDays == 0)
		return 0;
	else if (nYears == 0 && nMonths == 0)
		return nDays;
	else if (nYears == 0)
		return nMonths;
	else
		return nYears;
}

int CGessDate::CompareNow() const
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);

	struct tm* stTime = localtime(&tmNow);

	int nMonths, nDays, nYears;
	nYears = m_nYear - (stTime->tm_year + 1900);
	nMonths = m_nMonth - (stTime->tm_mon + 1);
	nDays = m_nDay - stTime->tm_mday;

	if (nYears == 0 && nMonths == 0 && nDays == 0)
		return 0;
	else if (nYears == 0 && nMonths == 0)
		return nDays;
	else if (nYears == 0)
		return nMonths;
	else
		return nYears;
}

CGessDate& CGessDate::operator++(int)
{
	int nDay = m_nDay + 1;
	if (nDay > m_nDayTab[IsLeap(m_nYear)][m_nMonth])
	{
		m_nDay = 1;
		m_nMonth++;
		if (m_nMonth > 12)
		{
			m_nMonth = 1;
			m_nYear++;
		}
	}
	else
	{
		m_nDay = nDay;
	}

	m_nWeekDay = (m_nWeekDay + 1) % 7;
	return *this;
}

CGessDate& CGessDate::operator+=(int nDayDiff)
{
	if (nDayDiff < 0)
		return operator-=(-nDayDiff);

	for (int i = 1; i <= nDayDiff; i++)
	{
		(*this)++;
	}
	return *this;
}

CGessDate& CGessDate::operator-=(int nDayDiff)
{
	if (nDayDiff > 0)
		return operator-=(-nDayDiff);

	for (int i = 1; i <= nDayDiff; i++)
	{
		(*this)--;
	}
	return *this;
}

CGessDate& CGessDate::operator--(int)
{
	if (m_nDay == 1)
	{
		if (m_nMonth == 1)
		{
			m_nYear--;
			m_nDay = 31;
			m_nMonth = 12;
		}
		else
		{
			m_nMonth--;
			m_nDay = m_nDayTab[IsLeap(m_nYear)][m_nMonth];
		}
	}
	else
	{
		m_nDay--;
	}
	m_nWeekDay = (m_nWeekDay + 6) % 7;
	return *this;
}

CGessDate CGessDate::operator+(int nDays) const
{
	CGessDate oDate(m_nYear, m_nMonth, m_nDay);
	if (nDays == 0)
	{
		return oDate;
	}
	else if (nDays > 0)
	{
		for (int i = 1; i <= nDays; i++)
		{
			oDate++;
		}
		return oDate;
	}
	else
	{
		return operator-(-nDays);
	}
}

CGessDate CGessDate::operator-(int nDays) const
{
	CGessDate oDate(m_nYear, m_nMonth, m_nDay);
	if (nDays == 0)
	{
		return oDate;
	}
	else if (nDays > 0)
	{
		for (int i = 1; i <= nDays; i++)
		{
			oDate--;
		}
		return oDate;
	}
	else
	{
		return operator+(-nDays);
	}
}

int CGessDate::IntervalToToday()
{
	CGessDate oToday;
	return oToday - *this;
}

int CGessDate::ThisYear()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	return stTime->tm_year + 1900;
}

int CGessDate::ThisMonth()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	return stTime->tm_mon + 1;
}

int CGessDate::ThisDay()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	return stTime->tm_mday;
}

int CGessDate::ThisIntergerFormat()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	return (stTime->tm_year + 1900) * 10000 + (stTime->tm_mon + 1) * 100 + stTime->tm_mday;
}

int CGessDate::ThisWeekDay()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm  stTime;
	//localtime_r(&tmNow,&stTime);

	struct tm* stTime = localtime(&tmNow);

	return stTime->tm_wday;
}

int CGessDate::WeekDay(int y, int m, int d)
{
	//蔡勒（Zeller）公式。即w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1 
	//公式中的符号含义如下
	//w：星期；c：世纪；y：年（两位数）；
	//m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算
	//比如2003年1月1日要看作2002年的13月1日来计算）；
	//d：日；[ ]代表取整，即只要整数部分。
	//(C是世纪数减一，y是年份后两位，M是月份，d是日数。
	//1月和2月要按上一年的13月和 14月来算，这时C和y均按上一年取值。)
	//若要计算的日期是在1582年10月4日或之前,为另外公式
	int c = 0;
	if (1 == m || 2 == m)
	{
		m += 12;
		y--;
	}

	c = y / 100;
	y = y % 100;

	int p2 = y / 4, p3 = c / 4, p5 = 26 * (m + 1) / 10;
	int w = y + p2 + p3 - 2 * c + p5 + d - 1;
	if (w >= 0)
	{
		return w % 7;
	}
	else
	{
		return 7 + w % 7;
	}
}

bool CGessDate::IsToday()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	int nMonth = stTime->tm_mon + 1;
	int nDay = stTime->tm_mday;
	int nYear = stTime->tm_year + 1900;

	return (nMonth == m_nMonth && nDay == m_nDay &&  nYear == m_nYear);
}

void CGessDate::Day2Today()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	m_nMonth = stTime->tm_mon + 1;
	m_nDay = stTime->tm_mday;
	m_nYear = stTime->tm_year + 1900;
	m_nWeekDay = stTime->tm_wday;
}

string CGessDate::ToString(const string& sSeprator)
{
	std::stringstream ss;
	ss << setfill('0') << setw(4) << m_nYear;

	string sTmp = trim(sSeprator);
	if (sTmp == "")
	{
		ss << setfill('0') << setw(2) << m_nMonth;
		ss << setfill('0') << setw(2) << m_nDay;
	}
	else
	{
		ss << sTmp;
		ss << setfill('0') << setw(2) << m_nMonth;
		ss << sTmp;
		ss << setfill('0') << setw(2) << m_nDay;
	}

	return ss.str();
}

string CGessDate::ToString(time_t t, const string& sSeprator)
{
	//struct tm  stTime;
	//localtime_r(&t,&stTime);
	struct tm* stTime = localtime(&t);

	std::stringstream ss;
	ss << setfill('0') << setw(4) << stTime->tm_year + 1900;

	string sTmp = trim(sSeprator);
	if (sTmp == "")
	{
		ss << setfill('0') << setw(2) << stTime->tm_mon + 1;
		ss << setfill('0') << setw(2) << stTime->tm_mday;
	}
	else
	{
		ss << sTmp;
		ss << setfill('0') << setw(2) << stTime->tm_mon + 1;
		ss << sTmp;
		ss << setfill('0') << setw(2) << stTime->tm_mday;
	}
	return ss.str();
}

string CGessDate::NowToString(const string& sSeprator)
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	int nMonth = stTime->tm_mon + 1;
	int nDay = stTime->tm_mday;
	int nYear = stTime->tm_year + 1900;

	std::stringstream ss;
	ss << setfill('0') << setw(4) << nYear;

	string sTmp = trim(sSeprator);
	if (sTmp == "")
	{
		ss << setfill('0') << setw(2) << nMonth;
		ss << setfill('0') << setw(2) << nDay;
	}
	else
	{
		ss << sTmp;
		ss << setfill('0') << setw(2) << nMonth;
		ss << sTmp;
		ss << setfill('0') << setw(2) << nDay;
	}

	return ss.str();
}

CGessDate CGessDate::InitialDate()
{
	return CGessDate(1900, 1, 1);
}

void CGessDate::ToInitialVal()
{
	m_nYear = 1900;
	m_nMonth = 1;
	m_nDay = 1;
	m_nWeekDay = 0;
}

CGessDate& CGessDate::operator-()
{
	m_nMonth = -m_nMonth;
	m_nDay = -m_nDay;
	m_nYear = -m_nYear;
	return *this;
}

EnumYearLeap CGessDate::IsLeap(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
	{
		return E_YEAR_LEAP;
	}
	else
	{
		return E_YEAR_LEAP_NON;
	}
}