#include "AirportSecuritySystemSimulator.h"

AirportSecuritySystemSimulator::AirportSecuritySystemSimulator(unsigned simulatedDays)
    : totalSimulationDay{ simulatedDays }
{
    timer = std::make_shared<SimulatedTimePublisher>();
    credentialsQueue = std::make_shared<PassengerCheckPointListener>("credentialsQueue", LAMBDA_PASSENGER_ARRIVAL, nullptr, 0.0, 20.0);
    credentialsCheckStation = std::make_shared<PassengerCheckPointListener>("credentialsCheckStation", LAMBDA_CREDENTIAL_STATION, credentialsQueue);
    scanningStationQueue = std::make_shared<PassengerCheckPointListener>("scanningStationQueue", LAMBDA_SCANNING_QUEUE, credentialsCheckStation);
    scanningStations[0] = std::make_shared<PassengerCheckPointListener>("scanningStations[0]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[1] = std::make_shared<PassengerCheckPointListener>("scanningStations[1]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[2] = std::make_shared<PassengerCheckPointListener>("scanningStations[2]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    scanningStations[3] = std::make_shared<PassengerCheckPointListener>("scanningStations[3]", LAMBDA_SCANNING_STATION, scanningStationQueue);
    infoProcessor = std::make_shared<ProcessInfoListener>(simulationRecord);
    infoProcessor->addUpstream(scanningStations[0]);
    infoProcessor->addUpstream(scanningStations[1]);
    infoProcessor->addUpstream(scanningStations[2]);
    infoProcessor->addUpstream(scanningStations[3]);
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
    double simulationEndTime = totalSimulationDay * SECONDS_PER_DAY;
    while (timer->getCurrentTime() < simulationEndTime)
    {
        timer->incrementTime();
    }
    simulationRecord.simulatedDays = totalSimulationDay;
    double averageQueue1Time = simulationRecord.totalQueue1Time / simulationRecord.passengerCount;
    double averageStation1Time = simulationRecord.totalStation1Time / simulationRecord.passengerCount;
    double averageQueue2Time = simulationRecord.totalQueue2Time / simulationRecord.passengerCount;
    double averageStation2Time = simulationRecord.totalStation2Time / simulationRecord.passengerCount;
    std::cout << "[Simulation record for " << simulationRecord.simulatedDays << " days]" << std::endl;
    std::cout << "passengerCount = " << simulationRecord.passengerCount << std::endl;
    std::cout << "totalQueue1Time = " << simulationRecord.totalQueue1Time << ", average = " << averageQueue1Time << " seconds." << std::endl;
    std::cout << "totalStation1Time = " << simulationRecord.totalStation1Time << ", average = " << averageStation1Time << " seconds." << std::endl;
    std::cout << "totalQueue2Time = " << simulationRecord.totalQueue2Time << ", average = " << averageQueue2Time << " seconds." << std::endl;
    std::cout << "totalStation2Time = " << simulationRecord.totalStation2Time << ", average = " << averageStation2Time << " seconds." << std::endl;
    std::cout << "total wait time per person = " << (averageQueue1Time + averageStation1Time + averageQueue2Time + averageStation2Time) / 60 << " minutes." << std::endl;
}