// EN.605.604.SU23_Project2.cpp : Defines the entry point for the application.

#include <iostream>
#include "Passenger.h"

using namespace std;

int main()
{
	cout << "Hello Project 2." << endl;
    // Passenger class.
    Passenger p1;
    cout << p1.getStartTime() << endl;
    p1.setStartTime(1234);
    cout << p1.getStartTime() << endl;
	return 0;
}
