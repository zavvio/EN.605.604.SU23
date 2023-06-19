#pragma once

#include <iostream>

class Memory
{
public:
    Memory(int initValue = 0);
    void addValue(int incrementValue);
    void resetValue();
    int getValue() const;

private:
    int value { 0 };
};