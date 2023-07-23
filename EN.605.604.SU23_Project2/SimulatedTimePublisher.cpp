#include "SimulatedTimePublisher.h"

SimulatedTimePublisher::~SimulatedTimePublisher()
{
#ifdef DEBUG_TRACE
    std::cout << "SimulatedTimePublisher terminated." << std::endl;
#endif
}

double SimulatedTimePublisher::getCurrentTime() const
{
    return simulatedTime;
}

void SimulatedTimePublisher::incrementTime(double increment)
{
    notify(simulatedTime);
    simulatedTime += increment;
    //std::cout << "time = " << simulatedTime << std::endl;
}