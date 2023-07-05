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

void SelectionButton::press()
{
    activated = true;
}

void SelectionButton::reset()
{
    activated = false;
}