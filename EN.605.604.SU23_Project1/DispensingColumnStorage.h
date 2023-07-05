#pragma once
#include "DrinkStorage.h"

class DispensingColumnStorage : public DrinkStorage
{
public:
    DispensingColumnStorage(const unsigned count = 5) : DrinkStorage(count) {};
    virtual ~DispensingColumnStorage();
    std::string getDrinkName() const;
    double getDrinkPrice() const;
};