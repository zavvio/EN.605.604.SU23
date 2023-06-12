// EN.605.604.SU23_Assignment1.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    cout << "==================== Testing Constructor: ====================" << endl;
    cout << "date {}" << endl;
    Date date1{};
    date1.showDate();
    cout << "date { 29 }" << endl;
    Date date2(29);
    date2.showDate();
    cout << "date { 29, 2 }" << endl;
    Date date3(29, 2);
    date3.showDate();
    cout << "date { 29, 2, 2024 }" << endl;
    Date date4(29, 2, 2024);
    date4.showDate();
    cout << "date { -10, -5, -12345 }" << endl;
    Date date5(-10, -5, -12345);
    date5.showDate();
    cout << "date { -10, -5, 12345 }" << endl;
    Date date6(-10, -5, 12345);
    date6.showDate();
    cout << "date { -10, 5, 12345 }" << endl;
    Date date7(-10, 5, 12345);
    date7.showDate();

    cout << endl << "==================== Testing Set functions: ====================" << endl;
    date4.setDay(30);
    date4.setYear(2023);
    date4.setDay(28);
    date4.setYear(2023);
    date4.showDate();
    date4.setDay(12345);
    date4.setMonth(12345);
    date4.setMonth(10);
    date4.setDay(31);
    date4.showDate();
    date4.setMonth(11);
    date4.setMonth(0);
    date4.setDay(0);
    date4.setYear(0);
    date4.setMonth(-5);
    date4.setDay(-10);
    date4.setYear(-12345);

    cout << endl << "==================== Testing Get functions: ====================" << endl;
    cout << "Date.getDay() = " << date4.getDay() << endl;
    cout << "Date.getMonth() = " << date4.getMonth() << endl;
    cout << "Date.getYear() = " << date4.getYear() << endl;
    cout << "Date.getStrMonth() = " << date4.getStrMonth() << endl;

    cout << endl << "==================== Testing comparison functions: ====================" << endl;
    cout << "Date 1: " << endl;
    date3.showDate();
    cout << "Date 2: " << endl;
    date4.showDate();
    cout << "Date 1 < Date 2? " << boolalpha << (date3 < date4) << endl;
    cout << "Date 1 == Date 2? " << (date3 == date4) << endl;
    cout << "Date1.setDate(31, 10, 2023)" << endl;
    date3.setDate(31, 10, 2023);
    date3.showDate();
    cout << "Date 1 < Date 2? " << (date3 < date4) << endl;
    cout << "Date 1 == Date 2? " << (date3 == date4) << endl;
    return 0;
}
