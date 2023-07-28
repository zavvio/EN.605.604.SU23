#include "Movie.h"

Movie::Movie(std::string name, int year)
    : name{ name }, year{ year }
{}

std::string Movie::getName() const
{
    return name;
}

int Movie::getYear() const
{
    return year;
}