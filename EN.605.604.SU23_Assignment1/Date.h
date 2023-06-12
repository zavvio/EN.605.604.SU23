#pragma once

#include <iostream>
#include <string>

enum class ErrorCode
{
    NO_ERROR = 0,
    INVALID_DAY,
    INVALID_MONTH,
    INVALID_YEAR
};

class Date
{
public:
    Date(int day = 1, int month = 1, int year = 1);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getStrMonth();
    ErrorCode setDay(int day);
    ErrorCode setMonth(int month);
    ErrorCode setYear(int year);
    ErrorCode setDate(int day = 1, int month = 1, int year = 1);
    void showDate();
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;

private:
    int day { 1 };
    int month { 1 };
    int year { 1 };
    std::string str_month { "January" };

    bool isLeapYear(const int& year);
    bool isValidDay(const int& day);
    bool isValidMonth(const int& month);
    bool isValidYear(const int& year);
    int getDaysInMonth(const int& month);
    void setStrMonth(const int& month);
    void showError(ErrorCode error, const int& value);
};