#include "Date.h"
using namespace std;

Date::Date()                                // default constructor
{
	Day = 0; Month = 0; Year = 0;
}

Date::Date(int d = 0, int m = 0, int y = 0)     // user defined constructor
	: Day(d), Month(m), Year(y)
{
	//
}

int Date::get_day()         // getters of date class ..
{
	return Day;
}
int Date::get_month()
{
	return Month;
}
int Date::get_year()
{
	return Year;
}

bool Date::validate()       // member function to check if the date is valid or not
{
	if (Year < 1970 || Year > 9999) return false;
	if (Month < 1 || Month >12) return false;
	if (Day < 1 || Day>31) return false;
	if (Month == 4 || Month == 6 || Month == 9 || Month == 11) return (Day < 31);
	if (Month == 2)
		return (isKabesa(Year)) ? (Day < 30) : (Day < 29);
	return true;
}

ostream& operator << (ostream& os, Date &c)        // overload  << operator to print the date object
{
	os << c.Day << "/" << c.Month << "/" << c.Year;
	return os;
}
istream& operator >> (istream& is, Date& c)         // overload  >> operator to read the date 
{
	Date tmp(0, 0, 0);
	c = tmp;
	int d(0), m(0), y(0);
	bool flag = true;
	is >> d;
	if (is.fail())
	{
		is.clear();
		cin.ignore(1000, '\n');
		return is;
	}
	if (is.get() != '/')
	{
		cout << "\n   Sorry .. This is Invalid! .. enter the date like(dd/mm/yyyy).\n";
		return is;
	}
	is >> m;
	if (is.fail())
	{
		is.clear();
		cin.ignore(1000, '\n');
		return is;
	}
	if (is.get() != '/')
	{
		cout << "\n   Sorry .. This is Invalid! .. enter the date like(dd/mm/yyyy).\n";
		return is;
	}
	is >> y;
	if (is.fail())
	{
		is.clear();
		cin.ignore(1000, '\n');
		return is;
	}
	c.setDate(d, m, y);
	return is;
}

Date Date::operator + (int x)       // member function to increment a specified date with a specified integer value
{
	Date tmp(*this);
	tmp.Day += x;

	while (!tmp.validate())
	{
		if (tmp.Month == 2)
		{
			if (isKabesa(Year))
				if ((tmp.Day - 29) > 0) {tmp.Day -= 29; tmp.Month++; }
				else break;
			else
				if ((tmp.Day - 28) > 0) { tmp.Day -= 28; tmp.Month++; }
				else break;
		}
		else if(tmp.Month == 4 || tmp.Month == 6 || tmp.Month == 9 || tmp.Month == 11)
		{
			if ((tmp.Day - 30) > 0) { tmp.Day -= 30;  tmp.Month++; }
			else break;
		}
		else
			if ((tmp.Day - 31) > 0) { tmp.Day -= 31;  tmp.Month++; }
			else break;
		if (tmp.Month > 12) { tmp.Month = 1; tmp.Year++; }

	}
	return tmp;
}

void Date::setDate(int d, int m, int y)        // member Function to set Date 
{
	Date tmp(d, m, y);
	if (tmp.validate()) *this = tmp;
	else { cout << "\n   Sorry .. ( "; cout << tmp; cout << " ) is Invalid Date .\n"; }
}

bool isKabesa(int year)               //  function to check if the year is kabesa or not
{
	return ((year % 4 == 0 && year % 100) || (year % 400 == 0));
}