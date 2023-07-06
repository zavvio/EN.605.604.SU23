#include "DispensingColumnStorage.h"

DispensingColumnStorage::~DispensingColumnStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "DispensingColumnStorage of type ";
#endif
}

// This is not a fixed value, it is dynamically retrieved from the first available drink.
std::string DispensingColumnStorage::getDrinkName() const
{
    if (isEmpty())
    {
        return "Empty";
    }
    return drinks[0]->getName();
}

// This is not a fixed value, it is dynamically retrieved from the first available drink.
double DispensingColumnStorage::getDrinkPrice() const
{
    if (isEmpty())
    {
        return 0.0;
    }
    return drinks[0]->getPrice();
}