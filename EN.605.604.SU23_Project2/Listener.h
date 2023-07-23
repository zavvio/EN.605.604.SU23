#pragma once
#include "DevUtil.h"

class Listener
{
public:
    virtual void update(double currTime) = 0; // Listeners will implement code
};