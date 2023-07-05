#include "MoneyStorage.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

MoneyStorage::MoneyStorage(unsigned count)
{
    for (const MoneyType& type : moneyType)
    {
        moneyCount[type] = count;
    }
}

MoneyStorage::~MoneyStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "MoneyStorage destroyed." << std::endl;
#endif
}

double MoneyStorage::getTotalValue(std::map<MoneyType, unsigned>* money)
{
    if (money == nullptr)
    {
        money = &moneyCount;
    }
    double total = 0.0;
    for (const MoneyType& type : moneyType)
    {
        total += (double) mapMoneyTypeToUnsignedValue(type) * (*money)[type] / 100;
    }
    return total;
}

//unsigned MoneyStorage::getCount(MoneyType type) const
//{
//    return moneyCount.at(type);
//}

void MoneyStorage::insertMoney(MoneyType type, unsigned count)
{
    moneyCount.at(type) += count;
}

void MoneyStorage::insertMoney(std::map<MoneyType, unsigned> money)
{
    for (const MoneyType& type : moneyType)
    {
        moneyCount.at(type) += money.at(type);
    }
}

unsigned MoneyStorage::dispenseMoney(MoneyType type, unsigned count)
{
    if (moneyCount.at(type) >= count)
    {
        moneyCount.at(type) -= count;
        return count;
    }
    return 0;
}

std::map<MoneyType, unsigned> MoneyStorage::dispenseMoney(double amount)
{
    unsigned count, amount_100bp_int = (unsigned) std::round(amount * 100);
    using enum MoneyType;
    std::map<MoneyType, unsigned> dispenseCount;

    for (int i = static_cast<int>(MoneyType::INVALID) - 1; i >= 0; i--)
    {
        count = amount_100bp_int / mapMoneyTypeToUnsignedValue(moneyType[i]);
        count = std::min(count, moneyCount.at(moneyType[i]));
        moneyCount.at(moneyType[i]) -= count;
        dispenseCount[moneyType[i]] = count;
        amount_100bp_int -= mapMoneyTypeToUnsignedValue(moneyType[i]) * count;
    }

    //showMoneyCount();
    return dispenseCount;
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

unsigned MoneyStorage::mapMoneyTypeToUnsignedValue(MoneyType type) const
{
    switch (type)
    {
    case MoneyType::NICKEL:
        return 5;
    case MoneyType::DIME:
        return 10;
    case MoneyType::QUARTER:
        return 25;
    case MoneyType::ONE_DOLLAR:
        return 100;
    case MoneyType::FIVE_DOLLAR:
        return 500;
    case MoneyType::TEN_DOLLAR:
        return 1000;
    case MoneyType::TWENTY_DOLLAR:
        return 2000;
    default:
        return 0;
    }
}

void MoneyStorage::showMoneyCount(std::map<MoneyType, unsigned>* money)
{
#ifdef DEBUG_TRACE
    if (money == nullptr)
    {
        money = &moneyCount;
    }
    std::cout << "Money count:" << std::endl;
    for (const MoneyType& type : moneyType)
    {
        std::cout << "$" << std::fixed << std::setprecision(2) << (double) mapMoneyTypeToUnsignedValue(type) / 100 << "\t= " << (*money)[type] << std::endl;
    }
#endif
}