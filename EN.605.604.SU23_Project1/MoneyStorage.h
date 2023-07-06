#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include "DevUtil.h"

// All supported money type, can be used to filter out unwanted or fake currency.
enum class MoneyType
{
    NICKEL,
    DIME,
    QUARTER,
    ONE_DOLLAR,
    FIVE_DOLLAR,
    TEN_DOLLAR,
    TWENTY_DOLLAR,
    INVALID,
};

// A helper structure to iterate through all supported money types since enum class doesn't support iteration.
const MoneyType moneyType[static_cast<int>(MoneyType::INVALID)] {
    MoneyType::NICKEL,
    MoneyType::DIME,
    MoneyType::QUARTER,
    MoneyType::ONE_DOLLAR,
    MoneyType::FIVE_DOLLAR,
    MoneyType::TEN_DOLLAR,
    MoneyType::TWENTY_DOLLAR
};

// MoneyStorage is essentially a giant wallet or ATM which stores and keeps track of money;
// for a vending machine, both the main coin/bill slot and the change return slot are of such type;
// they both need to store money and keep track of the number of each type of currencies.
class MoneyStorage
{
public:
    MoneyStorage(unsigned count = 0);
    virtual ~MoneyStorage();
    double getTotalValue(std::map<MoneyType, unsigned>* money = nullptr);
    unsigned getCount(MoneyType type) const;
    void insertMoney(MoneyType type, unsigned count = 1);
    void insertMoney(std::map<MoneyType, unsigned> money);
    unsigned dispenseMoney(MoneyType type, unsigned count = 1);
    std::map<MoneyType, unsigned> dispenseMoney(double amount);

protected:
    unsigned mapMoneyTypeToUnsignedValue(MoneyType type) const;

private:
    std::map<MoneyType, unsigned> moneyCount;

    void showMoneyCount(std::map<MoneyType, unsigned>* money = nullptr);
};