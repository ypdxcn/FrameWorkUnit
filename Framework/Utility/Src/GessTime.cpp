#include <ostream>
#include <istream>
#include <time.h>
#include <assert.h>
#include "GessTime.h"

std::ostream& operator<<(std::ostream& os, const CGessTime& t)
{
	os << t.m_nHour << ':' << t.m_nMinute << ':' << t.m_nSecond;
	return os;
}

std::istream& operator >> (std::istream& is, CGessTime& t)
{
	char slash;
	is >> t.m_nMinute >> slash >> t.m_nSecond >> slash >> t.m_nHour;
	return is;
}

CGessTime::CGessTime()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	m_nMinute = stTime->tm_min;
	m_nSecond = stTime->tm_sec;
	m_nHour = stTime->tm_hour;
}

CGessTime::CGessTime(int h, int m, int s)
{
	if (h == 24 && m == 0 && s == 0)
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
		return;
	}

	bool blValid = true;
	if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
	{
		blValid = false;
	}

	if (!blValid)
	{
		time_t tmNow;
		time(&tmNow);
		//struct tm stTime;
		//localtime_r(&tmNow,&stTime);
		struct tm* stTime = localtime(&tmNow);


		m_nMinute = stTime->tm_min;
		m_nSecond = stTime->tm_sec;
		m_nHour = stTime->tm_hour;
	}
	else
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
	}
}

CGessTime::CGessTime(int nTime)
{
	int h = nTime / 10000;
	int m = (nTime % 10000) / 100;
	int s = nTime % 100;
	//CGessTime(h,m,s);
	if (h == 24 && m == 0 && s == 0)
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
		return;
	}

	bool blValid = true;
	if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
	{
		blValid = false;
	}

	if (!blValid)
	{
		time_t tmNow;
		time(&tmNow);
		//struct tm stTime;
		//localtime_r(&tmNow,&stTime);
		struct tm* stTime = localtime(&tmNow);

		m_nMinute = stTime->tm_min;
		m_nSecond = stTime->tm_sec;
		m_nHour = stTime->tm_hour;
	}
	else
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
	}
}

CGessTime::CGessTime(const CGessTime& oTime)
{
	m_nSecond = oTime.m_nSecond;
	m_nMinute = oTime.m_nMinute;
	m_nHour = oTime.m_nHour;
}

CGessTime::CGessTime(const string& sTime, const string& sSeprator)
{
	bool blValid = true;
	int h, m, s;
	string sTmp = trim(sTime);

	size_t iPos = string::npos;
	if (0 != sSeprator.length())
	{
		iPos = sTime.find(sSeprator.at(0), 0);
	}
	if (string::npos != iPos)
	{
		vector<string> vTime = strutils::explodeQuoted(sSeprator, sTmp);
		size_t nSize = vTime.size();
		if (3 == nSize)
		{
			h = strutils::FromString<int>(vTime[0]);
			m = strutils::FromString<int>(vTime[1]);
			s = strutils::FromString<int>(vTime[2]);

			if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
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
		if (nLen != 6)
		{
			blValid = false;
		}
		else
		{
			h = strutils::FromString<int>(sTmp.substr(0, 2));
			m = strutils::FromString<int>(sTmp.substr(2, 2));
			s = strutils::FromString<int>(sTmp.substr(4, 2));

			if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
			{
				blValid = false;
			}
		}
	}

	if (blValid)
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
	}
	else
	{
		m_nMinute = 0;
		m_nSecond = 0;
		m_nHour = 0;
	}
}

bool CGessTime::FromString(const string& sTime, const string& sSeprator)
{
	bool blValid = true;
	int h, m, s;
	string sTmp = trim(sTime);

	size_t iPos = string::npos;
	if (0 != sSeprator.length())
	{
		iPos = sTime.find(sSeprator.at(0), 0);
	}
	if (string::npos != iPos)
	{
		vector<string> vTime = strutils::explodeQuoted(sSeprator, sTmp);
		size_t nSize = vTime.size();
		if (3 == nSize)
		{
			h = strutils::FromString<int>(vTime[0]);
			m = strutils::FromString<int>(vTime[1]);
			s = strutils::FromString<int>(vTime[2]);

			if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
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
		if (nLen != 6)
		{
			blValid = false;
		}
		else
		{
			h = strutils::FromString<int>(sTmp.substr(0, 2));
			m = strutils::FromString<int>(sTmp.substr(2, 2));
			s = strutils::FromString<int>(sTmp.substr(4, 2));

			if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
			{
				blValid = false;
			}
		}
	}

	if (blValid)
	{
		m_nSecond = s;
		m_nMinute = m;
		m_nHour = h;
	}
	return blValid;
}


std::string CGessTime::ToString(const string& sSeprator) const
{
	std::stringstream ss;
	string sTmp = trim(sSeprator);
	ss << setfill('0') << setw(2) << m_nHour;
	ss << sTmp;
	ss << setfill('0') << setw(2) << m_nMinute;
	ss << sTmp;
	ss << setfill('0') << setw(2) << m_nSecond;

	return ss.str();
}

std::string CGessTime::ToString(time_t t, const string& sSeprator)
{
	//struct tm stTime;
	//localtime_r(&t,&stTime);
	struct tm* stTime = localtime(&t);

	std::stringstream ss;
	string sTmp = trim(sSeprator);
	ss << setfill('0') << setw(2) << stTime->tm_hour;
	ss << sTmp;
	ss << setfill('0') << setw(2) << stTime->tm_min;
	ss << sTmp;
	ss << setfill('0') << setw(2) << stTime->tm_sec;
	return ss.str();
}

int CGessTime::IntervalToNow() const
{
	CGessTime oNow;
	int nInterval = oNow - *this;
	if (nInterval < 0)
		nInterval = SECOND_PER_DAT + nInterval;
	return nInterval;
}

void CGessTime::ToNow()
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	m_nMinute = stTime->tm_min;
	m_nSecond = stTime->tm_sec;
	m_nHour = stTime->tm_hour;
}

std::string CGessTime::NowToString(const string& sSeprator)
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);

	int nMinute = stTime->tm_min;
	int nSecond = stTime->tm_sec;
	int nHour = stTime->tm_hour;

	std::stringstream ss;
	string sTmp = trim(sSeprator);
	ss << setfill('0') << setw(2) << nHour;
	ss << sTmp;
	ss << setfill('0') << setw(2) << nMinute;
	ss << sTmp;
	ss << setfill('0') << setw(2) << nSecond;

	return ss.str();
}

CGessTime CGessTime::InitialTime()
{
	return CGessTime(0, 0, 0);
}

void CGessTime::ToInitialVal()
{
	m_nSecond = 0;
	m_nMinute = 0;
	m_nHour = 0;
}

CGessTime& CGessTime::operator++(int)
{
	m_nSecond++;
	if (m_nSecond >= 60)
	{
		m_nSecond -= 60;
		m_nMinute++;
		if (m_nMinute >= 60)
		{
			m_nMinute -= 60;
			m_nHour++;
			if (m_nHour >= 24)
			{
				m_nHour = 0;
			}
		}
	}
	return *this;
}

CGessTime& CGessTime::operator--(int)
{
	if (m_nSecond == 0)
	{
		m_nSecond = 59;
		if (m_nMinute >= 1)
		{
			m_nMinute--;
		}
		else
		{
			m_nMinute = 59;
			if (m_nHour >= 1)
			{
				m_nHour--;
			}
			else
			{
				m_nHour = 23;
			}
		}
	}
	else
	{
		m_nSecond--;
	}
	return *this;
}

CGessTime& CGessTime::operator+=(int nSecondChange)
{
	if (0 == nSecondChange)
		return *this;

	if (nSecondChange < 0)
		return operator-=(-nSecondChange);

	int nHourDiff = nSecondChange / 3600;
	int nMinuteDiff = (nSecondChange % 3600) / 60;
	int nSecondDiff = nSecondChange - nHourDiff * 3600 - nMinuteDiff * 60;

	m_nMinute += (m_nSecond + nSecondDiff) / 60;
	m_nHour += (m_nMinute + nMinuteDiff) / 60;
	m_nHour = (m_nHour + nHourDiff) % 24;
	m_nMinute = (m_nMinute + nMinuteDiff) % 60;
	m_nSecond = (m_nSecond + nSecondDiff) % 60;
	return *this;
}

CGessTime& CGessTime::operator-=(int nSecondChange)
{
	if (0 == nSecondChange)
		return *this;

	if (nSecondChange < 0)
		return operator+=(-nSecondChange);

	int nHourDiff = nSecondChange / 3600;
	int nMinuteDiff = (nSecondChange % 3600) / 60;
	int nSecondDiff = nSecondChange - nHourDiff * 3600 - nMinuteDiff * 60;

	if (m_nSecond >= nSecondDiff)
	{
		m_nSecond -= nSecondDiff;
	}
	else
	{
		m_nSecond = m_nSecond + 60 - nSecondDiff;
		m_nMinute--;
	}

	if (m_nMinute >= nMinuteDiff)
	{
		m_nMinute -= nMinuteDiff;
	}
	else
	{
		m_nMinute = m_nMinute + 60 - nMinuteDiff;
		m_nHour--;
	}

	if (m_nHour >= nHourDiff)
	{
		m_nHour -= nHourDiff;
	}
	else
	{
		m_nHour = m_nHour + 24 - nHourDiff;
	}
	return *this;
}

CGessTime CGessTime::operator+(int nSecondChange) const
{
	if (0 == nSecondChange)
		return *this;

	if (nSecondChange < 0)
		return operator-(-nSecondChange);

	int nHourDiff = nSecondChange / 3600;
	int nMinuteDiff = (nSecondChange % 3600) / 60;
	int nSecondDiff = nSecondChange - nHourDiff * 3600 - nMinuteDiff * 60;

	int nSecond = m_nSecond;
	int nMinute = m_nMinute;
	int nHour = m_nHour;
	nMinute += (nSecond + nSecondDiff) / 60;
	nHour += (nMinute + nMinuteDiff) / 60;
	nHour = (nHour + nHourDiff) % 24;
	nMinute = (nMinute + nMinuteDiff) % 60;
	nSecond = (nSecond + nSecondDiff) % 60;
	return CGessTime(nHour, nMinute, nSecond);
}

CGessTime CGessTime::operator-(int nSecondChange) const
{
	if (0 == nSecondChange)
		return *this;

	if (nSecondChange < 0)
		return operator+(-nSecondChange);

	int nHourDiff = nSecondChange / 3600;
	int nMinuteDiff = (nSecondChange % 3600) / 60;
	int nSecondDiff = nSecondChange - nHourDiff * 3600 - nMinuteDiff * 60;

	int nSecond = m_nSecond;
	int nMinute = m_nMinute;
	int nHour = m_nHour;
	if (nSecond >= nSecondDiff)
	{
		nSecond -= nSecondDiff;
	}
	else
	{
		nSecond = nSecond + 60 - nSecondDiff;
		nMinute--;
	}

	if (nMinute >= nMinuteDiff)
	{
		nMinute -= nMinuteDiff;
	}
	else
	{
		nMinute = nMinute + 60 - nMinuteDiff;
		nHour--;
	}

	if (nHour >= nHourDiff)
	{
		nHour -= nHourDiff;
	}
	else
	{
		nHour = nHour + 24 - nHourDiff;
	}
	return CGessTime(nHour, nMinute, nSecond);
}

int CGessTime::operator-(const CGessTime& t2) const
{
	if (*this == t2)
	{
		return 0;
	}
	else if (*this > t2)
	{
		int nMinute = m_nMinute;
		int nSecond = m_nSecond;
		int nHour = m_nHour;
		if (nSecond < t2.m_nSecond)
		{
			nSecond += 60;
			if (nMinute < 1)
			{
				nMinute += 59;
				nHour--;
			}
			else
			{
				nMinute--;
			}
		}

		if (nMinute < t2.m_nMinute)
		{
			nMinute += 60;
			nHour--;
		}
		return 3600 * (nHour - t2.m_nHour) + 60 * (nMinute - t2.m_nMinute) + (nSecond - t2.m_nSecond);
	}
	else
	{
		int nMinute = t2.m_nMinute;
		int nSecond = t2.m_nSecond;
		int nHour = t2.m_nHour;
		if (nSecond < m_nSecond)
		{
			nSecond += 60;
			if (nMinute < 1)
			{
				nMinute += 59;
				nHour--;
			}
			else
			{
				nMinute--;
			}
		}

		if (nMinute < m_nMinute)
		{
			nMinute += 60;
			nHour--;
		}
		return 3600 * (m_nHour - nHour) + 60 * (m_nMinute - nMinute) + (m_nSecond - nSecond);
	}
}

int CGessTime::Compare(const CGessTime& t2) const
{
	int nMinute, nSecond, nHour;

	nHour = m_nHour - t2.m_nHour;
	nMinute = m_nMinute - t2.m_nMinute;
	nSecond = m_nSecond - t2.m_nSecond;

	if (nHour == 0 && nMinute == 0 && nSecond == 0)
		return 0;
	else if (nHour == 0 && nMinute == 0)
		return nSecond;
	else if (nHour == 0)
		return nMinute;
	else
		return nHour;
}



CGessTime& CGessTime::operator-()
{
	m_nSecond = -m_nSecond;
	m_nMinute = -m_nMinute;
	m_nHour = -m_nHour;
	return *this;
}

CGessTime& CGessTime::operator=(const CGessTime& t2)
{
	m_nSecond = t2.m_nSecond;
	m_nMinute = t2.m_nMinute;
	m_nHour = t2.m_nHour;
	return *this;
}

int CGessTime::CompareNow() const
{
	time_t tmNow;
	time(&tmNow);
	//struct tm stTime;
	//localtime_r(&tmNow,&stTime);
	struct tm* stTime = localtime(&tmNow);


	int nMinute, nSecond, nHour;
	nHour = m_nHour - stTime->tm_hour;
	nMinute = m_nMinute - stTime->tm_min;
	nSecond = m_nSecond - stTime->tm_sec;

	if (nHour == 0 && nMinute == 0 && nSecond == 0)
		return 0;
	else if (nHour == 0 && nMinute == 0)
		return nSecond;
	else if (nHour == 0)
		return nMinute;
	else
		return nHour;
}