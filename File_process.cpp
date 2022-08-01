#include"File_process.h"
using namespace std;


int date_comp(Date a, Date b)     // function to compare two dates
{
	if (a.get_year() > b.get_year()) return 1;
	else if (a.get_year() < b.get_year()) return -1;
	else
		if (a.get_month() > b.get_month()) return 1;
		else if (a.get_month() < b.get_month()) return -1;
		else
			if (a.get_day() > b.get_day()) return 1;
			else if (a.get_day() < b.get_day()) return -1;
			else
				return 0;
}

void print_arr(Employee* arr, int size)  // function to print the an array of employees
{
	int i;
	cout << "   The number of employees = " << size << endl << endl;
	cout << "   Full Name\t\tSalary\tBirthdate\tHiredate" << endl << "   --------------------------------------------------------" << endl;
	for (i = 0; i < size; i++)
		cout << "   " << arr[i] << endl;
}

void asc_hire(Employee* arr, int size)   // function for arranging employees in ascending order according to hiredate
{
	int i;
	bool flag = true;
	Employee tmp;

	while (flag)
	{
		flag = false;
		for (i = 0; i < (size - 1); i++)
		{
			if (date_comp(arr[i].get_hire(), arr[i+1].get_hire()) == 1)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				flag = true;
			}
		}
	}
	print_arr(arr, size);
}

void asc_salary(Employee* arr, int size)   // function for arranging employees in ascending order according to salary
{
	int i;
	bool flag = true;
	Employee tmp;

	while (flag)
	{
		flag = false;
		for (i = 0; i < (size - 1); i++)
		{
			if (arr[i].get_salary() > arr[i + 1].get_salary())
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				flag = true;
			}
		}
	}
	print_arr(arr, size);
}

void hire_filter(Employee* old_arr, int size, Date date)  // Print employees whose hiredate is after a specified date
{
	int i, j(0), count(0);

	for (i = 0; i < size; i++)
		if (date_comp(date, old_arr[i].get_hire()) == -1)
			++count;

	Employee* new_arr = new Employee[count];

	for(i = 0; j < count; i++)
		if (date_comp(date, old_arr[i].get_hire()) == -1)
		{
			new_arr[j] = old_arr[i];
			++j;
		}

	asc_hire(new_arr, count);
	delete[] new_arr;
}

void incr_hire(string fileName)
{
	string fullname;
	int size, i, j, days;
	bool flag = false;

	ifstream read_emp;
	ofstream write_emp;

	cout << "\n   Enter the fullname of the employee you need : ";
	cin.ignore();
	getline(cin, fullname);

	read_emp.open(fileName, ios::in);
	if (!read_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
	else
	{
		read_emp >> size;
		Employee* emp_arr = new Employee[size];
		for (i = 0; i < size; i++)
		{
			read_emp >> emp_arr[i];
			if ((emp_arr[i].get_firstname() + " " + emp_arr[i].get_lastname()) == fullname)
			{
				j = i;
				flag = true;
			}
		}
		read_emp.close();

		if (flag)
		{
			cout << "\n   The employee has been found, enter the days you need to add to the hiredate : "; cin >> days;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				days = 0;
				cout << "\n   Sorry .. Invalid input.";
				flag = false;
			}
			if (flag)
			{
				Date date = emp_arr[j].get_hire() + days;
				emp_arr[j].set_hire(date);
				cout << endl << "   " << emp_arr[j] << endl;
				write_emp.open(fileName, ios::out | ios::trunc);
				if (!write_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
				else
				{
					write_emp << size << endl;
					for (i = 0; i < size; i++)
						write_emp << emp_arr[i] << endl;
					write_emp.close();

					cout << "\n   File modification completed successfully.";
				}
				cin.ignore();
			}
		}
		else cout << "\n   Sorry .. There is no employee with that name.";
		delete[] emp_arr;
	}
}

void find_emp_sal(Employee* old_arr, int size, int sal)
{
	Employee emp;
	int i, j(0), count(0);
	for (i = 0; i < size; i++)
		if (old_arr[i].get_salary() == sal) ++count;
	Employee* new_arr = new Employee[count];
	for (i = 0; j < count; i++)
	{
		if (old_arr[i].get_salary() == sal)
		{
			new_arr[j] = old_arr[i];
			++j;
		}
	}
	print_arr(new_arr, count);
	delete[] new_arr;
}

void add_emp(string fileName)    // function to add an employee to file of employees
{
	Employee new_emp;
	int size, i;

	ifstream read_emp;
	ofstream write_emp;

	read_emp.open(fileName, ios::in);
	if (!read_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
	else
	{
		read_emp >> size;
		Employee* emp_arr = new Employee[size + 1];
		for (i = 1; i < (size + 1); i++)
			read_emp >> emp_arr[i];
		read_emp.close();

		cout << "\n   enter the new employee : ";
		cin >> new_emp;
		if (new_emp.get_salary() == -1) cout << "\n   Sorry..The employee wasn't added, becauce the salary is invalid.";
		else if (new_emp.get_hire().validate() && new_emp.get_birth().validate())
		{
			emp_arr[0] = new_emp;

			write_emp.open(fileName, ios::out | ios::trunc);
			if (!write_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
			else
			{
				write_emp << size + 1 << endl;
				for (i = 0; i < (size + 1); i++)
					write_emp << emp_arr[i] << endl;
				write_emp.close();

				cout << "\n   The employee is added successfuly";
			}
			cin.ignore();
		}
		else cout << "\n   Sorry..The employee wasn't added, becauce the date is invalid.";
			delete[] emp_arr;
	}
}

void delete_emp(string fileName)  // function to delete a specified employee from the file
{
	string fullName;
	int size, i, j;
	bool flag = false;
	ifstream read_emp;
	ofstream write_emp;

	read_emp.open(fileName, ios::in);
	if (!read_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
	else

	{
		read_emp >> size;
		Employee* emp_arr = new Employee[size];
		for (i = 0; i < size; i++)
			read_emp >> emp_arr[i];
		read_emp.close();

		cout << "\n   Enter the fullname of the employee you need delete him : ";
		cin.ignore();
		getline(cin, fullName);

		for (i = 0; i < size; i++) // to find the employee
		{
			if ((emp_arr[i].get_firstname() + " " + emp_arr[i].get_lastname()) == fullName)
			{
				flag = true;
				j = i;
				break;
			}
		}

		if (flag)
		{
			char ch;
			cout << "\n   The employee has been found, are you sure you want to delete him ? (y/Y for yes) : "; cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				write_emp.open(fileName, ios::out | ios::trunc);
				if (!write_emp.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
				else
				{
					write_emp << size - 1 << endl;
					for (i = 0; i < size; i++)
					{
						if (i == j) continue;
						write_emp << emp_arr[i] << endl;
					}
					write_emp.close();

					cout << "\n   The employee is deleted successfuly .";
				}
			}
			else cout << "\n   Ok .. thanks .";
			cin.ignore();
		}
		else cout << "\n   There in no employee with that name .";
		
		delete[] emp_arr;
	}
}


void print_list()      // function to print the menu
{
	cout << "\n\t\t\t\t     -----<<   EMPLOYEES FILE PROGRAM   >>-----" << endl << endl;
	cout << "\n   1:) Change the file you need to proccess. "
		<< "\n   2:) Read and print all employees from the file."
		<< "\n   3:) Print employees whose hiredate is after a specified date."
		<< "\n   4:) Print the employees in ascending order according to specified field."
		<< "\n   5:) Increase the hire date of a specified employee a certain number of days."
		<< "\n   6:) Find the employees who have a specified salary."
		<< "\n   7:) Add an employee to the front of the file."
		<< "\n   8:) Delete a specified employee from the file."
		<< "\n   9:) Exit."
		<< "\n   ------------------------------";
}