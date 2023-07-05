#pragma once
#include <iostream>
#include <string>
#include "DevUtil.h"

class Drink
{
public:
    Drink() = delete;
    Drink(std::string name, double price);
    ~Drink();
    std::string getName() const;
    double getPrice() const;

private:
    std::string name;
    double price;
};