#pragma once
#include "DevUtil.h"

class Passenger
{
public:
    Passenger() = default;
    ~Passenger();
    void logTime(double time);
    double getQueue1Time() const;
    double getStation1Time() const;
    double getQueue2Time() const;
    double getStation2Time() const;

private:
    unsigned stage { 0 };
    double queue1EntryTime  { std::nan("") };
    double queue1ExitTime   { std::nan("") };
    double station1ExitTime { std::nan("") };
    double queue2ExitTime   { std::nan("") };
    double station2ExitTime { std::nan("") };
};
