#include "UserInterface.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

// Both Counter and Memory objects are not expected / allowed to change ever.
UserInterface::UserInterface(Counter& c, Memory& m) : aCounter{ c }, aMemory{ m } {};

void UserInterface::executeSelection()
{
    while (menuChoice != 6)
    {
        displayChoices();
        getUserInput();
        switch (menuChoice)
        {
        case 1:
            aCounter.incrementCount();
            displayOutput();
            break;
        case 2:
            aCounter.decrementCount();
            displayOutput();
            break;
        case 3:
            aCounter.resetCount();
            displayOutput();
            break;
        case 4:
            aMemory.addValue(aCounter.returnCount());
            displayOutput();
            break;
        case 5:
            aMemory.resetValue();
            displayOutput();
            break;
        case 6:
            cout << "Program Ending." << endl;
            break;
        default:
            cerr << "[ERROR] Unrecognized menu choice." << endl;
        }
    }
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

// Choices here are from template in lecture slide;
// ideally, they should be of an enum class.
void UserInterface::displayChoices()
{
    string choices[] = {
        "1..increment counter",
        "2..decrement counter",
        "3..reset counter",
        "4..add memory",
        "5..reset memory",
        "6..quit"
    };

    for (int i = 0; i < 6; i++)
        cout << choices[i] << endl;
    cout << "Please enter one of the options [1 - 6]: ";
}

// Assumption: User will input an expected valid integer as option.
// No advanced parsing is done here for brevity.
void UserInterface::getUserInput()
{
    cin >> menuChoice;
}

void UserInterface::displayOutput()
{
    cout << "Current Count: " << aCounter.returnCount()
        << ", Current Memory: " << aMemory.getValue() << endl;
}
