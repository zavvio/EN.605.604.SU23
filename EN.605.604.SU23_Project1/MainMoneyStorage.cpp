#include "MainMoneyStorage.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

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

void MainMoneyStorage::setCurrentSessionValue(double value)
{
    currentSessionValue = value;
}

void MainMoneyStorage::insertMoney(MoneyType type, unsigned count)
{
    MoneyStorage::insertMoney(type, count);
    currentSessionValue += (double)mapMoneyTypeToUnsignedValue(type) * count / 100;
}

std::map<MoneyType, unsigned> MainMoneyStorage::dispenseMoney(double amount)
{
    std::map<MoneyType, unsigned> money = MoneyStorage::dispenseMoney(amount);
    currentSessionValue -= getTotalValue(&money);
    return money;
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================