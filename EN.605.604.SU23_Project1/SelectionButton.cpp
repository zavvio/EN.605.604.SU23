#include "SelectionButton.h"

SelectionButton::~SelectionButton()
{
#ifdef DEBUG_TRACE
    std::cout << "SelectionButton destoryed." << std::endl;
#endif
}

bool SelectionButton::isActivated() const
{
    return activated;
}

// Whenever the flag is set, the vending machine will take action next time it checks.
void SelectionButton::press()
{
    activated = true;
}

// Vending machine is responsible to unset the flag after processing such request.
void SelectionButton::reset()
{
    activated = false;
}