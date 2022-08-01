#pragma once
#include"Employee.h"
using namespace std;

// functions to perform operations on the files

int date_comp(Date, Date);  
void print_arr(Employee*, int);
void asc_hire(Employee*, int);
void asc_salary(Employee*, int);
void hire_filter(Employee*, int, Date);
void add_emp(string);
void delete_emp(string);
void print_list();
void find_emp_sal(Employee*, int, int);
void incr_hire(string);