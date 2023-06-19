#include "Counter.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

Counter::Counter(int initCount) : countValue{initCount} {}

void Counter::incrementCount()
{
    countValue++;
}

// The Counter does not support negative value.
void Counter::decrementCount()
{
    if (countValue > 0)
        countValue--;
}

void Counter::resetCount()
{
    countValue = 0;
}

int Counter::returnCount() const
{
    return countValue;
}
