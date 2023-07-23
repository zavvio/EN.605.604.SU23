#pragma once
#include <cmath>
#include <queue>
#include "DevUtil.h"
#include "Listener.h"
#include "Passenger.h"
#include "RandomEventTimeGenerator.h"

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
