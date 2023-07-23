#include "Publisher.h"

void Publisher::attach(std::shared_ptr<Listener> l)
{
    listeners.push_back(l);
}

void Publisher::detach(std::shared_ptr<Listener> l)
{
    listeners.remove(l);
}

void Publisher::notify(double value)
{
    std::list<std::shared_ptr<Listener>>::iterator p;
    for (p = listeners.begin(); p != listeners.end(); p++)
    {
        (*p)->update(value);
    }
}
