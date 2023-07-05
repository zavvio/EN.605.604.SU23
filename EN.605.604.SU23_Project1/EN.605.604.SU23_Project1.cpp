// EN.605.604.SU23_Project1.cpp : Defines the entry point for the application.

#include <iostream>
#include "VendingMachine.h"
#include "CommandLineUserInterface.h"
#include "DevUtil.h"

#include <map>
#include "MoneyStorage.h"

using namespace std;

int main()
{
    VendingMachine aMachine;
    CommandLineUserInterface anInterface{ aMachine };
    anInterface.execute();
    return 0;
}
