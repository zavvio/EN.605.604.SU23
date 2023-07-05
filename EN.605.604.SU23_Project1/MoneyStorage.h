#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include "DevUtil.h"

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

const MoneyType moneyType[static_cast<int>(MoneyType::INVALID)]{
    MoneyType::NICKEL,
    MoneyType::DIME,
    MoneyType::QUARTER,
    MoneyType::ONE_DOLLAR,
    MoneyType::FIVE_DOLLAR,
    MoneyType::TEN_DOLLAR,
    MoneyType::TWENTY_DOLLAR
};
 
class MoneyStorage
{
public:
    MoneyStorage(unsigned count = 0);
    virtual ~MoneyStorage();
    double getTotalValue(std::map<MoneyType, unsigned>* money = nullptr);
    //unsigned getCount(MoneyType type) const;
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