#include "Employee.h"
using namespace std;

Employee::Employee()                   // default constructor
{
	FirstName = LastName = "";
	Salary = 0;
	BirthDate.setDate(1, 1, 1970);
	HireDate.setDate(1, 1, 1970);
}

Employee::Employee(string fn, string ln, Date birth, Date hire)           // Parameterized constructor (4 arguments)
	: FirstName(fn), LastName(ln), BirthDate(birth), HireDate(hire)
{
	Salary = 0;
}

Date Employee::get_birth()       // getters for employee class
{
	return BirthDate;
}
Date Employee::get_hire()
{
	return HireDate;
}
int Employee::get_salary()
{
	return Salary;
}
string Employee::get_firstname()
{
	return FirstName;
}
string Employee::get_lastname()
{
	return LastName;
}
void Employee::set_hire(Date& date)
{
	HireDate = date;
}

ostream& operator << (ostream& os, Employee& c)         // friend function to overload (ostream << )
{
	string fullname = (c.FirstName + " " + c.LastName);
	os << fullname;
	if (fullname.length() < 5) os << "\t\t\t";
	else if(fullname.length() < 13) os << "\t\t";
	else os << "\t";
	os << c.Salary << "\t" << c.BirthDate;
	if (c.BirthDate.get_year() == 0) os << "\t\t";
	else os << "\t";
	os << c.HireDate;
	return os;
} 
istream& operator >> (istream& is, Employee& c)      // friend function to overload (istream >> )
{
	string fn(""), ln("");
	int salary(0);
	Date b(1, 1, 1970), h(1, 1, 1970);
	bool flag = true;
	is >> fn >> ln;
	is >> salary;
	if (is.fail())
	{
		is.clear();
		is.ignore(1000, '\n');
		flag = false;
		salary = -1;
	}
	if (flag)
	{
		is >> b;
		if (b.validate())
		{
			is >> h;
			if (!h.validate()) is.ignore();
		}
		else is.ignore(1000, '\n');
	}
	Employee tmp(fn, ln, b, h);
	tmp.setSalary(salary);
	c = tmp;
	return is;
}

void Employee::setSalary(int s)            // member function to set salary
{
	this->Salary = s;
}