#include "DispensingColumnStorage.h"

DispensingColumnStorage::~DispensingColumnStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "DispensingColumnStorage of type ";
#endif
}

std::string DispensingColumnStorage::getDrinkName() const
{
    if (isEmpty())
    {
        return "Empty";
    }
    return drinks[0]->getName();
}

double DispensingColumnStorage::getDrinkPrice() const
{
    return drinks[0]->getPrice();
}