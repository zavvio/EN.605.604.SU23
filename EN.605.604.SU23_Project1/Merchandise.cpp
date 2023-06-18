#include "Merchandise.h"

Merchandise::Merchandise(MerchandiseID id, int price)
{
    //
}

MerchandiseID Merchandise::getId() const
{
    return id;
}

std::string Merchandise::getName() const
{
    return name;
}

int Merchandise::getPrice() const
{
    return price;
}