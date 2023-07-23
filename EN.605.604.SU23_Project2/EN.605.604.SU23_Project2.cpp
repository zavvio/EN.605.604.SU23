// EN.605.604.SU23_Project2.cpp : Defines the entry point for the application.

//#include <cmath>
//#include <cstdlib>
#include <ctime>
#include <numeric>
#include <queue>
#include <vector>
#include "DevUtil.h"
//#include "Passenger.h"
//#include "PassengerCheckPointListener.h"
//#include "RandomEventTimeGenerator.h"
//#include "SimulatedTimePublisher.h"
#include "AirportSecuritySystemSimulator.h"

using namespace std;

//vector<double> generateEvents(double rateParameter, double duration)
//{
//    double currTime = 0.0;
//    
//}

#ifdef UNIT_TEST
void testTimer()
{
    cout << endl << "[Unittest] Timer ==============================" << endl;
    Timer timer;
    cout << "Current time = " << timer.getCurrentTime() << endl;
    timer.incrementTime();
    timer.incrementTime();
    timer.incrementTime();
    cout << "Current time = " << timer.getCurrentTime() << endl;
    timer.incrementTime(123.456);
    cout << "Current time = " << timer.getCurrentTime() << endl;
}

void testPassenger()
{
    cout << endl << "[Unittest] Passenger ==============================" << endl;
    double times[7]{ 1.5, 2.7, 4.367, 10.421, 15.856, 1.23, -2.46 };
    Passenger p1;
    cout << "getQueue1Time = " << p1.getQueue1Time() << endl;
    cout << "getStation1Time = " << p1.getStation1Time() << endl;
    cout << "getQueue2Time = " << p1.getQueue2Time() << endl;
    cout << "getStation2Time = " << p1.getStation2Time() << endl;
    cout << "Times = ";
    for (double& time : times)
    {
        p1.logTime(time);
        cout << time << " ";
    }
    cout << endl;
    cout << "getQueue1Time = " << p1.getQueue1Time() << endl;
    cout << "getStation1Time = " << p1.getStation1Time() << endl;
    cout << "getQueue2Time = " << p1.getQueue2Time() << endl;
    cout << "getStation2Time = " << p1.getStation2Time() << endl;
}

void testRandomEventTimeGenerator()
{
    cout << endl << "[Unittest] RandomEventTimeGenerator ==============================" << endl;
#ifdef EXPERIMENTAL
    RandomEventTimeGenerator passengerArrivalTimeGenerator{ LAMBDA_PASSENGER_ARRIVAL };
    passengerArrivalTimeGenerator.getAverageNextEventTime();
    passengerArrivalTimeGenerator.getAverageNextEventTime_cStyle();
    RandomEventTimeGenerator credentialCheckTimeGenerator{ LAMBDA_CREDENTIAL_STATION };
    credentialCheckTimeGenerator.getAverageNextEventTime();
    credentialCheckTimeGenerator.getAverageNextEventTime_cStyle();
    RandomEventTimeGenerator scanningTimeGenerator{ LAMBDA_SCANNING_STATION };
    scanningTimeGenerator.getAverageNextEventTime();
    scanningTimeGenerator.getAverageNextEventTime_cStyle();
#endif
}
#endif

//class CheckPoint
//{
//public:
//    void average()
//    {
//        vector<double> v;
//        double average = accumulate(v.begin(), v.end(), 0.0) / v.size();
//    }
//private:
//    queue<Passenger> passengers;
//};

int main()
{
    cout << fixed << setprecision(2);
	cout << "Hello Project 2." << endl;

    AirportSecuritySystemSimulator simulation(5);
    simulation.run();
    
#ifdef UNIT_TEST
    testTimer();
    testPassenger();
    testRandomEventTimeGenerator();
#endif
}