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

// Count the total money value from all the currencies combined.
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

// Retrive count of a specific money type.
unsigned MoneyStorage::getCount(MoneyType type) const
{
    return moneyCount.at(type);
}

// Add a specific type of money to the storage.
void MoneyStorage::insertMoney(MoneyType type, unsigned count)
{
    moneyCount.at(type) += count;
}

// Add a stash of currencies to the storage.
void MoneyStorage::insertMoney(std::map<MoneyType, unsigned> money)
{
    for (const MoneyType& type : moneyType)
    {
        moneyCount.at(type) += money.at(type);
    }
}

// Dispense a specific money type; only dispense if storage has sufficient currencies.
// Return value indicates how many counts of such money type is dispensed rather than its money value.
unsigned MoneyStorage::dispenseMoney(MoneyType type, unsigned count)
{
    if (moneyCount.at(type) >= count)
    {
        moneyCount.at(type) -= count;
        return count;
    }
    return 0;
}

// Dispense a stash of currencies as close to the requested amount as possible.
// Note that it prioritizes dispensing the largest money type first;
// for example, a single twenty dollar bill would be dispensed instead of 20 one dollar bills.
// It dispenses only what's available from the storage;
// smaller money type for the same money value will be dispensed if not enough larger money type is available.
// If there is not enough currency overall, it simply dispenses all it has.
// Note: calculation is done with unsigned variable type to avoid rounding issue of floating point numbers.
std::map<MoneyType, unsigned> MoneyStorage::dispenseMoney(double amount)
{
    // e.g. $37.849999 is represented as 3785
    unsigned count, amount_100bp_int = (unsigned) std::round(amount * 100);
    using enum MoneyType;
    std::map<MoneyType, unsigned> dispenseCount;

    for (int i = static_cast<int>(MoneyType::INVALID) - 1; i >= 0; i--)
    {
        count = amount_100bp_int / mapMoneyTypeToUnsignedValue(moneyType[i]);
        // only dispense what's available from storage.
        count = std::min(count, moneyCount.at(moneyType[i]));
        moneyCount.at(moneyType[i]) -= count; // take it away from storage.
        dispenseCount[moneyType[i]] = count; // put it into dispensing stash.
        // update remaining value after the current money type is dispensed.
        amount_100bp_int -= mapMoneyTypeToUnsignedValue(moneyType[i]) * count;
    }

    showMoneyCount();
    return dispenseCount;
}

//============================================================
//                    PROTECTED FUNCTIONS                    =
//============================================================

// Map each money type to it money value, at 100 base-point resolution.
// e.g. a Quarter worth $0.25 is represented as 25
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

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

// Print out all money type and their counts currently in storage.
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