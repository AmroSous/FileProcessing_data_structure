#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Date                                   ///  date class and its data and methods
{
private:
	int Day, Month, Year;

public:
	Date(int d, int m, int y);
	Date();
	int get_day();
	int get_month();
	int get_year();
	bool validate();
	void setDate(int d, int m, int y);
	friend ostream& operator << (ostream &, Date& c);
	friend istream& operator >> (istream&, Date& c);
	Date operator + (int x);
};
bool isKabesa(int year);                // prototype of a function that check if a year is kabesa or not