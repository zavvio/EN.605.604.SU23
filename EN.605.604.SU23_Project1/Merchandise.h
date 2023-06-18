#pragma once

#include <string>

enum class MerchandiseID
{
    INVALID = 0,
    COKE    = 1000,
    PEPSI   = 1001,
    MILK    = 1002
};

class Merchandise
{
public:
    Merchandise() = delete;
    Merchandise(MerchandiseID id, int price);
    MerchandiseID getId() const;
    std::string getName() const;
    int getPrice() const;

private:
    MerchandiseID id { MerchandiseID::INVALID };
    std::string name { "" };
    int price { 0 };
};