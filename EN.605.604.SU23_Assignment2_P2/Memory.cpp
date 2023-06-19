#include "Memory.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

Memory::Memory(int initValue) : value{initValue} {}

// Memory accumulates indead of being replaced as specified in assignment.
void Memory::addValue(int incrementValue)
{
    value += incrementValue;
}

void Memory::resetValue()
{
    value = 0;
}

int Memory::getValue() const
{
    return value;
}
