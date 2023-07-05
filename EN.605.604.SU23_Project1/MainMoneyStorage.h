#pragma once
#include <iostream>
#include "MoneyStorage.h"
#include "DevUtil.h"

class MainMoneyStorage : public MoneyStorage
{
public:
    MainMoneyStorage(unsigned count = 0) : MoneyStorage{ count } {};
    virtual ~MainMoneyStorage();
    double getCurrentSessionValue() const;
    void setCurrentSessionValue(double value);
    void insertMoney(MoneyType type, unsigned count = 1);
    std::map<MoneyType, unsigned> dispenseMoney(double amount);

private:
    double currentSessionValue{ 0.0 };
};