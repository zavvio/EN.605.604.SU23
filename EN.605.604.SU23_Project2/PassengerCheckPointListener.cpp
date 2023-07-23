#include "PassengerCheckPointListener.h"

PassengerCheckPointListener::PassengerCheckPointListener(std::string name, double eventLambda,
    std::shared_ptr<PassengerCheckPointListener> upstream, double startHour, double stopHour) :
    listenerName{ name }, eventTimeGenerator{ eventLambda }, upstream{ upstream },
    dailyOperatingStartHour{ startHour }, dailyOperatingStopHour{ stopHour }
{
    //
}

PassengerCheckPointListener::~PassengerCheckPointListener()
{
#ifdef DEBUG_TRACE
    std::cout << "[Listener " << listenerName << "] terminated." << std::endl;
#endif
}

void PassengerCheckPointListener::update(double currTime)
{
#ifdef DEBUG_TRACE
    //std::cout << "[Listener " << listenerName << "] currTime = " << currTime << std::endl;
#endif
    if (currTime >= availableAfterTime)
    {
        if (currPassenger != nullptr)
        {
            if (isOrigin())
            {
                currPassenger->logTime(currTime);
            }
            enqueue(currPassenger);
            //std::cout << "currPassenger = " << (currPassenger == nullptr ? "nullptr" : "not null") << std::endl;
        }

        if (isCheckPointOpen(currTime))
        {
            if (isOrigin())
            {
                currPassenger = std::make_unique<Passenger>();
                updateAvailableAfterTime(currTime);
            }
            else if (upstream->isPassengerAvailable())
            {
                currPassenger = upstream->dequeue();
                currPassenger->logTime(currTime);
#ifdef DEBUG_TRACE
                std::cout << " at " << currTime << "." << std::endl;
#endif
                updateAvailableAfterTime(currTime);
            }
        }
    }
}

bool PassengerCheckPointListener::isPassengerAvailable() const
{
    return !passedPassengers.empty();
}

std::unique_ptr<Passenger> PassengerCheckPointListener::dequeue()
{
    std::unique_ptr<Passenger> passenger = std::move(passedPassengers.front());
    passedPassengers.pop();
#ifdef DEBUG_TRACE
    std::cout << "Passenger left " << listenerName;
#endif
    return passenger;
}

bool PassengerCheckPointListener::isOrigin() const
{
    return (upstream == nullptr);
}

bool PassengerCheckPointListener::isCheckPointOpen(double currTime) const
{
    double secondsPerDay = 60.0 * 60 * 24;
    double timeInDay = std::fmod(currTime, secondsPerDay);
    double dailyOperatingStartSecond = 60.0 * 60 * dailyOperatingStartHour;
    double dailyOperatingStopSecond = 60.0 * 60 * dailyOperatingStopHour;
    return (timeInDay >= dailyOperatingStartSecond && timeInDay < dailyOperatingStopSecond);
}


void PassengerCheckPointListener::enqueue(std::unique_ptr<Passenger>& passenger)
{
    passedPassengers.push(std::move(passenger));
}

void PassengerCheckPointListener::updateAvailableAfterTime(double currTime)
{
    double nextTime = eventTimeGenerator.getNextEventTime();
    availableAfterTime = currTime + nextTime;

#ifdef DEBUG_TRACE
    if (nextTime > 1.0)
        std::cout << "[" << listenerName << "] currTime = " << currTime << ", nextEventTime +" << nextTime  << " = " << availableAfterTime << std::endl;
#endif
}