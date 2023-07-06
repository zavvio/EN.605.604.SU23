#include "MainMoneyStorage.h"

MainMoneyStorage::~MainMoneyStorage()
{
#ifdef DEBUG_TRACE
    std::cout << "MainMoneyStorage of type ";
#endif
}

double MainMoneyStorage::getCurrentSessionValue() const
{
    return currentSessionValue;
}

// Use to update current balance after a purchase.
void MainMoneyStorage::setCurrentSessionValue(double value)
{
    currentSessionValue = value;
}

// When money is inserted, keep track of such temporary balance prior to purchase or refund.
void MainMoneyStorage::insertMoney(MoneyType type, unsigned count)
{
    MoneyStorage::insertMoney(type, count);
    currentSessionValue += (double)mapMoneyTypeToUnsignedValue(type) * count / 100;
}

// Dispensing money also deduct its value from the current balance.
std::map<MoneyType, unsigned> MainMoneyStorage::dispenseMoney(double amount)
{
    std::map<MoneyType, unsigned> money = MoneyStorage::dispenseMoney(amount);
    currentSessionValue -= getTotalValue(&money);
    return money;
}