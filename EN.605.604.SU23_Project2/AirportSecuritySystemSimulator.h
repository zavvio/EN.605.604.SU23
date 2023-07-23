#pragma once
#include "DevUtil.h"
#include "PassengerCheckPointListener.h"
#include "ProcessInfoListener.h"
#include "Record.h"
#include "SimulatedTimePublisher.h"

const double LAMBDA_PASSENGER_ARRIVAL   = 1.0 / 40.0; // 1 passenger arrives every 40 seconds.
const double LAMBDA_CREDENTIAL_STATION  = 1.0 / 30.0; // 1 passenger checked every 30 seconds.
const double LAMBDA_SCANNING_QUEUE      = 1.0 / 0.01; // Instant; let's assume 1 passenger can pass every 0.01 second.
const double LAMBDA_SCANNING_STATION    = 1.0 / 150.0; // 1 passenger scanned every 150 seconds.

const double SECONDS_PER_DAY{ 60.0 * 60 * 24 };
const double SECOND_IN_DAY_TO_LOCK_QUEUE{ 60.0 * 60 * 20 };

class AirportSecuritySystemSimulator
{
public:
    AirportSecuritySystemSimulator(unsigned simulatedDays = 5);
    void run();

private:
    std::shared_ptr<SimulatedTimePublisher> timer;
    std::shared_ptr<PassengerCheckPointListener> credentialsQueue;
    std::shared_ptr<PassengerCheckPointListener> credentialsCheckStation;
    std::shared_ptr<PassengerCheckPointListener> scanningStationQueue;
    std::shared_ptr<PassengerCheckPointListener> scanningStations[4];
    std::shared_ptr<ProcessInfoListener> infoProcessor;
    const unsigned totalSimulationDay;
    Record simulationRecord;
};
