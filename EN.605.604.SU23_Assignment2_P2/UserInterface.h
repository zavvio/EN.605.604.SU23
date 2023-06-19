#pragma once

#include <iostream>
#include <string>
#include "Counter.h"
#include "Memory.h"

using namespace std;

class UserInterface
{
public:
    UserInterface(Counter& c, Memory& m);
    void executeSelection();

private:
    Counter& aCounter;
    Memory& aMemory;
    int menuChoice { 0 };

    void displayChoices();
    void getUserInput();
    void displayOutput();
};