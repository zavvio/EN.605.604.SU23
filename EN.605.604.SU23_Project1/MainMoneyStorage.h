#pragma once
#include <iostream>
#include "MoneyStorage.h"
#include "DevUtil.h"

// MainMoneyStorage is a specialized version of MoneyStorage,
// it is capable of keeping track of a temporary balance;
// the money value of such balance is used later for purchase and/or refund.
// If a purchase is made, only the balance is subtracted while the actual currencies are kept by the storage.
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
    // Money value / balance of currently inserted currencies prior to purchase or refund.
    double currentSessionValue{ 0.0 };
};