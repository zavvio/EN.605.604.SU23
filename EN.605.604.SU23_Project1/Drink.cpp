#include "Drink.h"

Drink::Drink(std::string name, double price)
    : name{ name }, price{ price } {}

Drink::~Drink()
{
#ifdef DEBUG_TRACE
    std::cout << "Drink consumed (destroyed)." << std::endl;
#endif
}

std::string Drink::getName() const
{
    return name;
}

double Drink::getPrice() const
{
    return price;
}