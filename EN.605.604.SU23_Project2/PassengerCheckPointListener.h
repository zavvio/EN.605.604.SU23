#pragma once
#include <cmath>
#include <queue>
#include "DevUtil.h"
#include "Listener.h"
#include "Passenger.h"
#include "RandomEventTimeGenerator.h"

// A check point may be a queue or a station.
// Each check point may hold some amount of passengers;
// the passenger will come from an upstream check point unless it is the origin;
// there is a "processing time",
// so the check point would only retrieve a passenger from upstream after each processing time interval;
// and the previously processed passenger would be moved to the check point's ready queue,
// for downstream check point's consumption.
//
// A check point subscribe to a time event publisher, which trigger a time event in fine grain.
// For each time event received, the check point would take action if it has passed the "processing time";
// otherwise, it will do nothing for the current time event, and wait for the next one.
//
// A check point may also specify its operational time within a day (24-hour period), e.g 6 am to 10 pm;
// no action would be processed during non-operational period.
class PassengerCheckPointListener : public Listener
{
public:
    PassengerCheckPointListener() = delete;
    PassengerCheckPointListener(std::string name, double eventLambda = 0.0, std::shared_ptr<PassengerCheckPointListener> upstream = nullptr, double startHour = 0.0, double stopHour = 24.0);
    ~PassengerCheckPointListener();
    void update(double currTime = 0.0) override;
    bool isPassengerAvailable() const;
    std::unique_ptr<Passenger> dequeue();

private:
    std::string listenerName;
    std::shared_ptr<PassengerCheckPointListener> upstream;
    double availableAfterTime{ 0.0 };
    RandomEventTimeGenerator eventTimeGenerator;
    std::unique_ptr<Passenger> currPassenger{ nullptr };
    std::queue<std::unique_ptr<Passenger>> passedPassengers;
    double dailyOperatingStartHour;
    double dailyOperatingStopHour;

    bool isOrigin() const;
    bool isCheckPointOpen(double currTime) const;
    void enqueue(std::unique_ptr<Passenger>& passenger);
    void updateAvailableAfterTime(double currTime);
};
