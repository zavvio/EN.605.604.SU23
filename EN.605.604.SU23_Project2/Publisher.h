#pragma once
#include <list>
#include "DevUtil.h"
#include "Listener.h"

class Publisher
{
public:
    void attach(std::shared_ptr<Listener> l);
    void detach(std::shared_ptr<Listener> l);
    void notify(double value = 0.0); // Notify all listeners
private:
    std::list<std::shared_ptr<Listener>> listeners;
};
