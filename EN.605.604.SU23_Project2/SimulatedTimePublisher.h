#pragma once
#include <list>
#include "DevUtil.h"
#include "Publisher.h"

class SimulatedTimePublisher : public Publisher
{
public:
    ~SimulatedTimePublisher();
    double getCurrentTime() const;
    void incrementTime(double increment = 1.0);
private:
    double simulatedTime{ 0.0 };
};
