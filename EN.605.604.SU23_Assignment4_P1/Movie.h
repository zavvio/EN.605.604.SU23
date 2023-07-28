#pragma once

#include "DevUtil.h"

class Movie
{
public:
    Movie(std::string name = "", int year = 2023);
    std::string getName() const;
    int getYear() const;

private:
    std::string name;
    int year;
};