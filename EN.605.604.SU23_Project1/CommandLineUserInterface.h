#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include "VendingMachine.h"

using namespace std;

class CommandLineUserInterface
{
public:
    CommandLineUserInterface(VendingMachine& machine);
    void execute();

private:
    VendingMachine& aMachine;
    unsigned menuChoice { 0 };

    const std::vector<string> mainMenuChoices = {
        "======================================================================\n"
        "Vending machine: current balance = $",
        "\t1 - insert money",
        "\t2 - press refund button",
        "\t3 - press button for dispensing column",
        "\t4 - get dispensed drink",
        "\t5 - get refund",
        "\t6 - quit"
    };

    const std::vector<string> moneyMenuChoices = {
        "======================================================================\n"
        "Vending machine: current balance = $",
        "\t1 - insert  a Nickel  ($0.05)",
        "\t2 - insert  a Dime    ($0.10)",
        "\t3 - insert  a Quarter ($0.25)",
        "\t4 - insert  1 Dollar  ($1.00)",
        "\t5 - insert  5 Dollar  ($5.00)",
        "\t6 - insert 10 Dollar ($10.00)",
        "\t7 - insert 20 Dollar ($20.00)",
        "\t8 - cancel"
    };

    void displayMainMenu() const;
    void displayMoneyMenu() const;
    void displayColumnMenu() const;
    void displayRefund(std::map<MoneyType, unsigned> refund) const;
    void getUserMenuInput(size_t maxOption);
    void processMoneyMenuInput();
    void processColumnMenuInput();
};