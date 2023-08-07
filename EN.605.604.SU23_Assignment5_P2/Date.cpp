#include "Date.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

// This constructor is declared with default parameter values, thus arguments are optional.
// Parameter values are checked against before assignment, so invalid date is impossible.
Date::Date(int day, int month, int year)
{
    setDate(day, month, year);
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

std::string Date::getStrMonth()
{
    return str_month;
}

// Set Day if valid; otherwise, prompt error and make no change.
ErrorCode Date::setDay(int day)
{
#ifdef DEBUG_TRACE
    std::cout << "Date.setDay(" << day << ")" << std::endl;
#endif
    if (isValidDay(day))
    {
        this->day = day;
        return ErrorCode::NO_ERROR;
    }
    else
    {
        showError(ErrorCode::INVALID_DAY, day);
        return ErrorCode::INVALID_DAY;
    }
}

// Set Month if valid; otherwise, prompt error and make no change.
ErrorCode Date::setMonth(int month)
{
#ifdef DEBUG_TRACE
    std::cout << "Date.setMonth(" << month << ")" << std::endl;
#endif
    if (isValidMonth(month))
    {
        this->month = month;
        setStrMonth(month);
        return ErrorCode::NO_ERROR;
    }
    else
    {
        showError(ErrorCode::INVALID_MONTH, month);
        return ErrorCode::INVALID_MONTH;
    }
}

// Set Year if valid; otherwise, prompt error and make no change.
ErrorCode Date::setYear(int year)
{
#ifdef DEBUG_TRACE
    std::cout << "Date.setYear(" << year << ")" << std::endl;
#endif
    if (isValidYear(year))
    {
        this->year = year;
        return ErrorCode::NO_ERROR;
    }
    else
    {
        showError(ErrorCode::INVALID_YEAR, year);
        return ErrorCode::INVALID_YEAR;
    }
}

ErrorCode Date::setDate(int day, int month, int year)
{
    ErrorCode error = ErrorCode::NO_ERROR;
    error = setYear(year);
    if (error != ErrorCode::NO_ERROR)
        return error;
    error = setMonth(month);
    if (error != ErrorCode::NO_ERROR)
        return error;
    error = setDay(day);
    if (error != ErrorCode::NO_ERROR)
        return error;
    return error;
}

void Date::showDate()
{
    std::cout << "Date.showDate() --> Day: " << day << ", Month = " << month
        << " (" << str_month << "), Year = " << year << std::endl;
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

bool Date::isLeapYear(const int& year)
{
    return ((year % 4) == 0 ? true : false);
}

// Day validity is dependent on current Month.
bool Date::isValidDay(const int& day)
{
    if (day > 0 && day <= getDaysInMonth(month))
    {
        return true;
    }
    return false;
}

// Month (to be changed to) is valid only if it doesn't violate current Day.
bool Date::isValidMonth(const int& month)
{
    if (month > 0 && month < 13)
    {
        if (day <= getDaysInMonth(month))
            return true;
        else
            return false;
    }
    return false;
}

// Year (to be changed to) must not violate current Month & Day (i.e. Feb 29 for leap year only).
bool Date::isValidYear(const int& year)
{
    if (year <= 0)
        return false;
    if (!isLeapYear(year) && month == 2 && day > 28)
        return false;
    return true;
}

// Hard-coded number of days per month to avoid complex logic.
int Date::getDaysInMonth(const int& month)
{
    switch (month)
    {
    case 2:
        return (isLeapYear(year) ? 29 : 28);
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 0;
    }
}

// Does not support raw string input from user for sake of simple logic.
void Date::setStrMonth(const int& month)
{
    switch (month)
    {
    case 1:
        str_month = "January";
        break;
    case 2:
        str_month = "February";
        break;
    case 3:
        str_month = "March";
        break;
    case 4:
        str_month = "April";
        break;
    case 5:
        str_month = "May";
        break;
    case 6:
        str_month = "June";
        break;
    case 7:
        str_month = "July";
        break;
    case 8:
        str_month = "August";
        break;
    case 9:
        str_month = "September";
        break;
    case 10:
        str_month = "October";
        break;
    case 11:
        str_month = "November";
        break;
    case 12:
        str_month = "December";
        break;
    default:
        // Should not be the case, takes no action.
        break;
    }
}

void Date::showError(ErrorCode error, const int& value)
{
    switch (error)
    {
    case ErrorCode::NO_ERROR:
        break;
    case ErrorCode::INVALID_DAY:
        std::cerr << value << " is not a valid day for Month(" << month << ") Year(" << year << "), value unchanged." << std::endl;
        break;
    case ErrorCode::INVALID_MONTH:
        std::cerr << value << " is not a valid month for Day(" << day << ") Year(" << year << "), value unchanged." << std::endl;
        break;
    case ErrorCode::INVALID_YEAR:
        std::cerr << value << " is not a valid year for Day(" << day << ") Month(" << month << "), value unchanged." << std::endl;
        break;
    default:
        std::cerr << "Unexpected ErrorCode: " << static_cast<int>(error) << std::endl;
        break;
    }
}

bool Date::operator==(const Date& other) const
{
    if (year == other.year && month == other.month && day == other.day)
        return true;
    return false;
}

bool Date::operator<(const Date& other) const
{
    if (year < other.year)
        return true;
    else if (year == other.year && month < other.month)
        return true;
    else if (year == other.year && month == other.month && day < other.day)
        return true;
    return false;
}