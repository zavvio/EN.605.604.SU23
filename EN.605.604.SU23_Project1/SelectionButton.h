#pragma once
#include "DrinkStorage.h"
#include "DevUtil.h"

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