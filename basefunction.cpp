#include "basefunction.h"
#include <sstream>
const unsigned long monthOfDay[12]={31,29,31,30,31,30,31,31,30,31,30,31};

string dateToString(unsigned long date)
{
	ostringstream dateStream;
	dateStream << getYear(date) << "-" << getMonth(date) << "-" << getDay(date) << endl;
	return dateStream.str();
}

unsigned long stringToDate(const string& dateString)
{
	char dump;
	unsigned long nYear,nMonth,nDay;
	istringstream dateStream(dateString);
	dateStream >> nYear >> dump >> nMonth >> dump >> nDay;
	if(dateStream.fail())
		return 0;
	return getDate(nYear,nMonth,nDay);
}
inline unsigned long getYear(unsigned long date)
{
	return date / 366;
}

inline unsigned long getMonth(unsigned long date)
{
	unsigned long dayOfYear = date % 366;
	int i = 0;
	while(dayOfYear > monthOfDay[i])
	{
		dayOfYear -= monthOfDay[i];
		i++;
	}
	return ++i;
}

inline unsigned long getDay(unsigned long date)
{
	unsigned long dayOfYear = date % 366;
	int i = 0;
	while(dayOfYear > monthOfDay[i])
	{
		dayOfYear -= monthOfDay[i];
		i++;
	}
	return dayOfYear;
}

unsigned long getDate(unsigned long year, unsigned long month, unsigned long day )
{
	unsigned long yearOfDay = 0;
	for(unsigned long i = 0; i < month - 1; i++)
	{
		yearOfDay += monthOfDay[i];
	}
	yearOfDay += day;

	return yearOfDay + year * 366;
}
