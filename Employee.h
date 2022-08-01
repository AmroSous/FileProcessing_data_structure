#pragma once
#include<string>
#include"Date.h"
using namespace std;

class Employee                                  ///  employee class and its data and methods
{
private:
	string FirstName, LastName;
	int Salary;
	Date BirthDate, HireDate;

public:
	Employee(string fn, string ln, Date birth, Date hire);
	Employee();
	Date get_birth();
	Date get_hire();
	int get_salary();
	string get_firstname();
	string get_lastname();
	void set_hire(Date&);
	friend ostream& operator << (ostream&, Employee&);
	friend istream& operator >> (istream&, Employee&);
	void setSalary(int);

};