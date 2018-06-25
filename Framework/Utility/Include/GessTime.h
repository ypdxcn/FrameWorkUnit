#ifndef _GESS_TIME_H_
#define _GESS_TIME_H_

#include "Gess.h"
#include "strutils.h"
#include <string>
#include <sstream>
#include <iomanip>

#define SECOND_PER_DAT 24 * 60 * 60
using namespace std;
using namespace strutils;

class istream;
class ostream;
class UTIL_CLASS CGessTime
{
	friend std::ostream& operator<<(std::ostream&, const CGessTime&);
	friend std::istream& operator >> (std::istream&, CGessTime&);
	friend class CGessDateTime;
public:
	CGessTime();
	CGessTime(int h, int m, int s);
	CGessTime(const CGessTime& oTime);
	CGessTime(const string& sTime, const string& sSeprator = ":");
	CGessTime(int nTime);

	inline int Second() const { return m_nSecond; }
	inline int Minute() const { return m_nMinute; }
	inline int Hour() const { return m_nHour; }
	inline int IntergerFormat() const { return m_nHour * 10000 + m_nMinute * 100 + m_nSecond; }

	static CGessTime InitialTime();
	void ToInitialVal();
	int IntervalToNow() const;
	void ToNow();
	bool FromString(const string & sTime, const string& sSeprator = ":");
	std::string ToString(const string& sSeprator = ":") const;
	static std::string ToString(time_t t, const string& sSeprator = ":");
	static std::string NowToString(const string& sSeprator = "");


	CGessTime& operator++(int);
	CGessTime& operator--(int);
	CGessTime& operator+=(int);
	CGessTime& operator-=(int);
	CGessTime operator+(int nSecond) const;
	CGessTime operator-(int nSecond) const;
	int operator-(const CGessTime& t2) const;
	CGessTime& operator-();
	CGessTime& operator=(const CGessTime& t2);

	bool operator<(const CGessTime& t2) const { return Compare(t2) < 0; }
	bool operator<=(const CGessTime& t2) const { return Compare(t2) <= 0; }
	bool operator>(const CGessTime& t2) const { return Compare(t2) > 0; }
	bool operator>=(const CGessTime& t2) const { return Compare(t2) >= 0; }
	bool operator==(const CGessTime& t2) const { return Compare(t2) == 0; }
	bool operator!=(const CGessTime& t2) const { return Compare(t2) != 0; }
	int Compare(const CGessTime&) const;
	int CompareNow() const;
private:
	int m_nSecond;
	int m_nMinute;
	int m_nHour;
};
#endif