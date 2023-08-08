#pragma once
#include "DevUtil.h"

// Base abstract class which has a time based event
class Listener
{
public:
    virtual void update(double currTime) = 0; // Concrete listeners will implement code
};