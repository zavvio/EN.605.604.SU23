#include "AirportSecuritySystemSimulator.h"

// A discrete event simulation for an airport security system (queue) over a time period
// The system is consist of:
// 1 credentials queue (1 passenger arrival every 40 seconds on average)
//   --> 1 credentials check station (1 check completes every 30 seconds on average)
//     --> 1 scanning station queue (instant pass-through if passenger is available)
//       --> 4 scanning stations (1 scan completes per station every 150 seconds on average)
//         --> (virtual) Data processor (gather passenger time info from all scanning station outputs)
// The simulation is time based (i.e. a time event every second);
// all time event subscribers shall determine if any actual work may be processed.
AirportSecuritySystemSimulator::AirportSecuritySystemSimulator(unsigned simulatedDays)
    : totalSimulationDay{ simulatedDays }
{
    // create time event publisher
    timer = std::make_shared<SimulatedTimePublisher>();

    // create time event subscriber
    credentialsQueue = std::make_shared<PassengerCheckPointListener>("credentialsQueue", LAMBDA_PASSENGER_ARRIVAL, nullptr, 0.0, 20.0);
    credentialsCheckStation = std::make_shared<PassengerCheckPointListener>("credentialsCheckStation", LAMBDA_CREDENTIAL_STATION, credentialsQueue);
    scanningStationQueue = std::make_shared<PassengerCheckPointListener>("scanningStationQueue", LAMBDA_SCANNING_QUEUE, credentialsCheckStation);
    scanningStations[0] = std::make_shared<PassengerCheckPointListener>("scanningStations[0]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[1] = std::make_shared<PassengerCheckPointListener>("scanningStations[1]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[2] = std::make_shared<PassengerCheckPointListener>("scanningStations[2]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[3] = std::make_shared<PassengerCheckPointListener>("scanningStations[3]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    infoProcessor = std::make_shared<ProcessInfoListener>(simulationRecord);

    // ProcessInfoListener retrieves Passenger from all 4 scanning stations
    infoProcessor->addUpstream(scanningStations[0]);
    infoProcessor->addUpstream(scanningStations[1]);
    infoProcessor->addUpstream(scanningStations[2]);
    infoProcessor->addUpstream(scanningStations[3]);

    // attaching all subscribers to the time event publisher
    timer->attach(credentialsQueue);
    timer->attach(credentialsCheckStation);
    timer->attach(scanningStationQueue);
    timer->attach(scanningStations[0]);
    timer->attach(scanningStations[1]);
    timer->attach(scanningStations[2]);
    timer->attach(scanningStations[3]);
    timer->attach(infoProcessor);
}

void AirportSecuritySystemSimulator::run()
{
    // trigger all time events
    double simulationEndTime = totalSimulationDay * SECONDS_PER_DAY;
    while (timer->getCurrentTime() < simulationEndTime)
    {
        timer->incrementTime();
    }

    // generate report based on all simulation data
    simulationRecord.simulatedDays = totalSimulationDay;
    double averageQueue1Time = simulationRecord.totalQueue1Time / simulationRecord.passengerCount;
    double averageStation1Time = simulationRecord.totalStation1Time / simulationRecord.passengerCount;
    double averageQueue2Time = simulationRecord.totalQueue2Time / simulationRecord.passengerCount;
    double averageStation2Time = simulationRecord.totalStation2Time / simulationRecord.passengerCount;
    std::cout << "The system was simulated for " << simulationRecord.simulatedDays << " days." << std::endl;
    std::cout << "A total of " << simulationRecord.passengerCount << " passengers were served by the security system." << std::endl;
    std::cout << "On average, " << simulationRecord.passengerCount / simulationRecord.simulatedDays << " passengers were served per day." << std::endl;
    double totalTime = averageQueue1Time + averageStation1Time + averageQueue2Time + averageStation2Time;
    std::cout << "On average, the total time in the system for a passenger (queue time + service time) is:" << std::endl;
    std::cout << "\t--> " << totalTime << " seconds (" << totalTime / 60 << " minutes)." << std::endl;
    totalTime = averageQueue1Time + averageQueue2Time;
    std::cout << "On average, the total wait time per passenger in the system (total time in queues) is:" << std::endl;
    std::cout << "\t--> " << totalTime << " seconds (" << totalTime / 60 << " minutes)." << std::endl;
    totalTime = averageQueue1Time + averageStation1Time;
    std::cout << "On average, the total time per passenger in stage 1 process (the credential validation station) is:" << std::endl;
    std::cout << "\t--> " << totalTime << " seconds (" << totalTime / 60 << " minutes)." << std::endl;
    totalTime = averageQueue2Time + averageStation2Time;
    std::cout << "On average, the total time per passenger in stage 2 process (the scanning station) is:" << std::endl;
    std::cout << "\t--> " << totalTime << " seconds (" << totalTime / 60 << " minutes)." << std::endl;

    std::cout << std::endl << std::endl << "========== Extra Stats ==========" << std::endl;
    std::cout << "totalQueue1Time   = " << std::left << std::setw(10) << simulationRecord.totalQueue1Time   << " seconds, average = " << std::left << std::setw(6) << averageQueue1Time   << " seconds (" << averageQueue1Time   / 60 << " minutes)." << std::endl;
    std::cout << "totalStation1Time = " << std::left << std::setw(10) << simulationRecord.totalStation1Time << " seconds, average = " << std::left << std::setw(6) << averageStation1Time << " seconds (" << averageStation1Time / 60 << " minutes)." << std::endl;
    std::cout << "totalQueue2Time   = " << std::left << std::setw(10) << simulationRecord.totalQueue2Time   << " seconds, average = " << std::left << std::setw(6) << averageQueue2Time   << " seconds (" << averageQueue2Time   / 60 << " minutes)." << std::endl;
    std::cout << "totalStation2Time = " << std::left << std::setw(10) << simulationRecord.totalStation2Time << " seconds, average = " << std::left << std::setw(6) << averageStation2Time << " seconds (" << averageStation2Time / 60 << " minutes)." << std::endl;
}