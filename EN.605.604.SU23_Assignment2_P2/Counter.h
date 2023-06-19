#pragma once

#include <iostream>

class Counter
{
public:
    Counter(int initCount = 0);
    void incrementCount();
    void decrementCount();
    void resetCount();
    int returnCount() const;

private:
    int countValue { 0 };
};