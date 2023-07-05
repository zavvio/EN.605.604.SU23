#include "DrinkStorage.h"

DrinkStorage::~DrinkStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "DrinkStorage destroyed." << std::endl;
#endif
}

bool DrinkStorage::isFull() const
{
    if (drinks.size() >= maxCount)
    {
        return true;
    }
    return false;
}

bool DrinkStorage::isEmpty() const
{
    if (drinks.size() <= 0)
    {
        return true;
    }
    return false;
}

unsigned DrinkStorage::getMaxCount() const
{
    return maxCount;
}

unsigned DrinkStorage::getCurrentCount() const
{
    return static_cast<unsigned>(drinks.size());
}

void DrinkStorage::insert(std::unique_ptr<Drink>& drink)
{
    drinks.push_back(std::move(drink));
}

std::unique_ptr<Drink> DrinkStorage::dispense()
{
    if (drinks.size() > 0)
    {
        std::unique_ptr<Drink> drink = std::move(drinks.front());
        drinks.pop_front();
        return drink;
    }
    else
    {
        return nullptr;
    }
}