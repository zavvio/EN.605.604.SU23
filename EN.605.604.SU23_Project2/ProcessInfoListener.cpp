#include "ProcessInfoListener.h"

ProcessInfoListener::~ProcessInfoListener()
{
#ifdef DEBUG_TRACE
    std::cout << "[Listener ProcessInfoListener] terminated." << std::endl;
#endif
}

void ProcessInfoListener::update(double currTime)
{
    std::unique_ptr<Passenger> passenger;
    for (auto& upstream : upstreams)
    {
        while (upstream->isPassengerAvailable())
        {
            passenger = upstream->dequeue();
#ifdef DEBUG_TRACE
            std::cout << " at " << currTime << "." << std::endl;
#endif
            passenger->logTime(currTime);
            record.passengerCount++;
            record.totalQueue1Time += passenger->getQueue1Time();
            record.totalStation1Time += passenger->getStation1Time();
            record.totalQueue2Time += passenger->getQueue2Time();
            record.totalStation2Time += passenger->getStation2Time();
            passenger = nullptr;
        }
    }
}

void ProcessInfoListener::addUpstream(std::shared_ptr<PassengerCheckPointListener>& upstream)
{
    upstreams.push_back(upstream);
}