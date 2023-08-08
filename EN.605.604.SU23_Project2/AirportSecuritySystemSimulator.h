#pragma once
#include "DevUtil.h"
#include "PassengerCheckPointListener.h"
#include "ProcessInfoListener.h"
#include "Record.h"
#include "SimulatedTimePublisher.h"

// Lambda constant for various exponential distribution
const double LAMBDA_PASSENGER_ARRIVAL  = 1.0 / 40.0;  // 1 passenger arrives every 40 seconds.
const double LAMBDA_CREDENTIAL_STATION = 1.0 / 30.0;  // 1 passenger completes check every 30 seconds.
const double LAMBDA_SCANNING_QUEUE     = 1.0 / 0.01;  // Instant, if available; let's assume 1 passenger can pass every 0.01 second.
const double LAMBDA_SCANNING_STATION   = 1.0 / 150.0; // 1 passenger completes scan every 150 seconds.

const double SECONDS_PER_DAY{ 60.0 * 60 * 24 };

class AirportSecuritySystemSimulator
{
public:
    AirportSecuritySystemSimulator(unsigned simulatedDays = 5);
    void run();

private:
    std::shared_ptr<SimulatedTimePublisher> timer;                     // publisher: control event flow
    std::shared_ptr<PassengerCheckPointListener> credentialsQueue;          // subscriber to time event
    std::shared_ptr<PassengerCheckPointListener> credentialsCheckStation;   // subscriber to time event
    std::shared_ptr<PassengerCheckPointListener> scanningStationQueue;      // subscriber to time event
    std::shared_ptr<PassengerCheckPointListener> scanningStations[4];       // subscriber to time event
    std::shared_ptr<ProcessInfoListener> infoProcessor;                     // subscriber to time event
    const unsigned totalSimulationDay;
    Record simulationRecord; // log all simulation data
};
