#include "DrinkStorage.h"

DrinkStorage::~DrinkStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "DrinkStorage destroyed." << std::endl;
#endif
}

// Use to add a drink into either the dispensing column or delivery slot.
// Theoretically, a dispensing column can store various kind of drinks,
// it is up to the application logic to guard against such logical error.
void DrinkStorage::insert(std::unique_ptr<Drink>& drink)
{
    drinks.push_back(std::move(drink));
}

// Check if there is any drink.
bool DrinkStorage::isEmpty() const
{
    if (drinks.size() <= 0)
    {
        return true;
    }
    return false;
}

// Dispense the first available drink if the storage is not empty.
std::unique_ptr<Drink> DrinkStorage::dispense()
{
    if (isEmpty())
    {
        return nullptr;
    }
    else
    {
        std::unique_ptr<Drink> drink = std::move(drinks.front());
        drinks.pop_front();
        return drink;
    }
}

// Can be used to prevent more drink from being added to the dispensing column / delivery slot if it's already full.
bool DrinkStorage::isFull() const
{
    if (drinks.size() >= maxCount)
    {
        return true;
    }
    return false;
}

// The maximum size of a dispensing column or delivery slot.
// Useful to simulate a realistic vending machine in the physical world with size limit.
unsigned DrinkStorage::getMaxCount() const
{
    return maxCount;
}

// Return how many drinks are currently in the dispensing column or delivery slot.
unsigned DrinkStorage::getCurrentCount() const
{
    return static_cast<unsigned>(drinks.size());
}