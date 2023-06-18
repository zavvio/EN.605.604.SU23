// EN.605.604.SU23_Assignment2_P1.cpp : Defines the entry point for the application.

#include <iostream>
#include "MyArray.h"

using namespace std;

int main()
{
	int tmp = 0;
	MyArray a1;
	cout << "A1 is created with default constructor." << endl;
	cout << "A1.getSize = " << a1.getSize() << endl << endl;

	MyArray a2(-5);
	cout << "A2 is created as MyArray(-5)." << endl;
	cout << "A2.getSize = " << a2.getSize() << endl << endl;

	MyArray a3(5);
	cout << "A3 is created as MyArray(5)." << endl;
	cout << "A3.getSize = " << a3.getSize() << endl;
	a3.setDataByIndex(5, 123);
	a3.setDataByIndex(2, 123);
	cout << "A3: ";
	a3.displayData();
	a3.getDataByIndex(2, tmp);
	cout << "A3[2] = " << tmp << endl << endl;

	cout << "A4 is being created as = A3." << endl;
	MyArray a4 = a3;
	cout << "A4.getSize = " << a4.getSize() << endl;
	cout << "A4: ";
	a4.displayData();
	a4.setDataByIndex(2, 777);
	cout << "A3: ";
	a3.displayData();
	cout << "A4: ";
	a4.displayData();
	cout << endl;
	
	return 0;
}
