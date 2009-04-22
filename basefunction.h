#ifndef BASEFUNCTION_HJC_20090422
#define BASEFUNCTION_HJC_20090422

#include <string>
using namespace std;

string dateToString(unsigned long date);
unsigned long stringToDate(const string& dateString);
unsigned long getYear(unsigned long date);
unsigned long getMonth(unsigned long date);
unsigned long getDay(unsigned long date);
unsigned long getDate(unsigned long year, unsigned long month, unsigned long day );
#endif
