#pragma once
#include "DrinkStorage.h"

// A dispensing column is a specialized version of drink storage,
// in order to support a potential transaction,
// it must be able to identify basic info of its next available drink.
// In reality, a dispensing column is most likely associated with a fixed drink and fixed price;
// however, in software world, it's possible to
// dynamically retrieve such info from the first available drink in the storage;
// it's up to the application logic to enforce all drinks being added to the storage are of same type, if necessary.
// In reality, a maintenance guy could have mixed in a wrong type of drink by mistake as well.
class DispensingColumnStorage : public DrinkStorage
{
public:
    DispensingColumnStorage(const unsigned count = 5) : DrinkStorage(count) {};
    virtual ~DispensingColumnStorage();
    std::string getDrinkName() const;
    double getDrinkPrice() const;
};