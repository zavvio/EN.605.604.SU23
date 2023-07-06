#pragma once
#include "DrinkStorage.h"
#include "DevUtil.h"

// With a proper framework, a button could employ a callback function approach;
// here, it's merely setting a flag upon being pressed;
// an active function call (or ideally a background thread) from the vending machine
// would check the flags for all available buttons, and take action as requested.
class SelectionButton
{
public:
    ~SelectionButton();
    bool isActivated() const;
    void press();
    void reset();
private:
    bool activated = false;
};