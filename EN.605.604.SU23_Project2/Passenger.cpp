#include "Passenger.h"

Passenger::~Passenger()
{
#ifdef DEBUG_TRACE
    std::cout << "Passenger dismissed (destroyed)." << std::endl;
#endif
}

void Passenger::logTime(double time)
{
    switch (stage++)
    {
    case 0:
#ifdef DEBUG_TRACE
        std::cout << "Passenger first shown up (constructed) at time: " << time << std::endl;
#endif
        queue1EntryTime = time;
        break;
    case 1:
        queue1ExitTime = time;
        break;
    case 2:
        station1ExitTime = time;
        break;
    case 3:
        queue2ExitTime = time;
        break;
    case 4:
        station2ExitTime = time;
        break;
    default:
        break;
    }
}

double Passenger::getQueue1Time() const
{
    if (isnan(queue1ExitTime) || isnan(queue1EntryTime))
    {
        return nan("");
    }
    return queue1ExitTime - queue1EntryTime;
}

double Passenger::getStation1Time() const
{
    if (isnan(station1ExitTime) || isnan(queue1ExitTime))
    {
        return nan("");
    }
    return station1ExitTime - queue1ExitTime;
}

double Passenger::getQueue2Time() const
{
    if (isnan(queue2ExitTime) || isnan(station1ExitTime))
    {
        return nan("");
    }
    return queue2ExitTime - station1ExitTime;
}

double Passenger::getStation2Time() const
{
    if (isnan(station2ExitTime) || isnan(queue2ExitTime))
    {
        return nan("");
    }
    return station2ExitTime - queue2ExitTime;
}