#pragma once
#include <iostream>
#include <string>
//#include "DevUtil.h"

class Passenger
{
public:
    Passenger() = default;
    ~Passenger() = default;
    unsigned getStartTime() const { return startTime; }
    void setStartTime(unsigned time) { startTime = time; }

private:
    unsigned startTime{0};
    unsigned stage1QueueTime{0};
    unsigned stage1StationTime{0};
    unsigned stage2QueueTime{0};
    unsigned stage2StationTime{0};
};
