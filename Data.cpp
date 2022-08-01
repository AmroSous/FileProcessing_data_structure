#include<cstdlib>
#include"Employee.h"
#include"File_process.h"
using namespace std;

int main()  // main function ..
{
	cout << "\n\t\t\t\t     -----<<   EMPLOYEES FILE PROGRAM   >>-----" << endl << endl;
	cout << "   Description :\tThis program allows the user to deal with an employees file,\n\t\t\tand perform several operations on it ." << endl << endl;
	cout << "   -------------------------------------------------------------------------\n";

	ofstream write_file;
	ifstream read_file;
	int size, i;
	string fileName;
	cout << "\n   Enter the name of the file you need to proccess (ex : filename.txt) : ";
	getline(cin, fileName);
	system("cls");// clean screen .. or system("clean") for linux

	print_list();
	cout << "\n   Choose from the list : ";
	int choice;
	cin >> choice;
	while (cin.fail() || choice < 1 || choice > 9) // check the choice correctness
	{
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		print_list();
		cout << "\n   Invalid input .. please choose from the list : ";
		cin >> choice;
	}

	while (choice != 9)  // loop for menu
	{
		switch (choice)
		{
		case 1:
		{
			cout << "\n   Enter the name of the file you need to proccess (ex : filename.txt) : ";
			cin.ignore();
			getline(cin, fileName);
			cout << "\n   The file changed successfully .";
		}
		break;

		case 2:
		{
			cout << endl;
			read_file.open(fileName, ios::in);
			if (!read_file.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
			else
			{
				bool flag;
				read_file >> size;
				Employee* emp_arr = new Employee[size];
				for (i = 0; i < size; i++) read_file >> emp_arr[i];
				read_file.close();
				print_arr(emp_arr, size);
				delete[] emp_arr;
			}
			cin.ignore();
		}
		break;

		case 3:
		{
			read_file.open(fileName, ios::in);
			if (!read_file.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
			else
			{
				read_file >> size;
				Employee* emp_arr = new Employee[size];
				for (i = 0; i < size; i++) read_file >> emp_arr[i];
				read_file.close();
				Date date;
				cout << "\n   Enter a specified date : "; cin >> date;
				if (date.validate())
				{
					cout << "\n   The employees whose hiredate is after " << date << " are : " << endl << endl;
					hire_filter(emp_arr, size, date);
					cin.ignore();
				}
				else cout << "\n   Sorry.. Invalid date.";
				delete[] emp_arr;
			}
		}
		break;

		case 4:
		{
			read_file.open(fileName, ios::in);
			if (!read_file.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
			else
			{
				int x;
				read_file >> size;
				Employee* emp_arr = new Employee[size];
				for (i = 0; i < size; i++) read_file >> emp_arr[i];
				read_file.close();

				cout << "\n   1) According to hiredate."
					<< "\n   2) According to  salary." << endl;
				cout << "\n   choose the field : "; cin >> x;

				while (x < 1 || x > 2)  // check the choice correctness
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n   Invalid choice .. choose from the menu : ";
					cin >> x;
				}

				if (x == 1)
				{
					cout << endl;
					asc_hire(emp_arr, size);
				}
				if (x == 2)
				{
					cout << endl;
					asc_salary(emp_arr, size);
				}
				delete[] emp_arr;
			}

			cin.ignore();
		}
		break;

		case 5:
		{
			incr_hire(fileName);
		}
		break;

		case 6:
		{
			read_file.open(fileName, ios::in);
			if (!read_file.is_open()) cout << "\n   OOH .. There was a failure to open the file :( .";
			else
			{
				int sal, j(0), count;
				cout << "\n   Enter a specified salary : "; cin >> sal;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n   Invalid input .. please enter a specified salary : ";
					cin >> sal;
				}
				read_file >> size;
				Employee* emp_arr = new Employee[size];
				for (i = 0; i < size; i++)
					read_file >> emp_arr[i];
				read_file.close();
				cout << "\n   The employees who have salary = " << sal << " are : " << endl << endl;
				find_emp_sal(emp_arr, size, sal);
				delete[] emp_arr;
			}
			cin.ignore();
		}
		break;

		case 7:
		{
			add_emp(fileName);
		}
		break;

		case 8:
		{
			delete_emp(fileName);
		}
		break;
		}

		cout << "\n\n   Press enter to choose another choice .. ";
		cin.get();
		system("cls"); // clean screen .. or system("clean") for linux
		print_list();
		cout << "\n   Choose from the list : ";
		cin >> choice; 
		while (cin.fail() || choice < 1 || choice > 9) // check the choice correctness
		{
			cin.clear();
			cin.ignore(1000, '\n');
			system("cls");
			print_list();
			cout << "\n   Invalid input .. please choose from the list : ";
			cin >> choice;
		}
	}

	cout << "\n   Ok .. thank you.\n\n\n";  // if exit 

	system("pause");  // pause the screen
	return EXIT_SUCCESS;  // finish program
}