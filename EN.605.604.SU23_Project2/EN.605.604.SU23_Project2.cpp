// EN.605.604.SU23_Project2.cpp : Defines the entry point for the application.

//#include <cmath>
//#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <queue>
#include <random>
#include <vector>
#include "Passenger.h"

using namespace std;

const double LAMBDA_PASSENGER_ARRIVAL   = 1.0 / 40.0;
const double LAMBDA_CREDENTIAL_STATION  = 1.0 / 30.0;
const double LAMBDA_SCANNING_STATION    = 1.0 / 150.0;

const double SECONDS_PER_DAY { 60.0 * 60 * 24 };
const double SECOND_IN_DAY_TO_LOCK_QUEUE { 60.0 * 60 * 20 };



vector<double> generateEvents(double rateParameter, double duration)
{
    double currTime = 0.0;
    
}

class RandomEventTimeGenerator
{
public:
    RandomEventTimeGenerator() = delete;
    RandomEventTimeGenerator(double lambda) :
        lambda{ lambda },
        distribution{ lambda },
        seed{ (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count() }
    {
        generator.seed(seed);
        
        // C Style - seed random number generator
        srand((unsigned) time(NULL));
    }

    double getNextEventTime()
    {
        return distribution(generator);;
    }

    double getAverageNextEventTime(unsigned occurence = 1000000)
    {
        double nextEventTime, totalTime = 0.0;
        for (unsigned i = 0; i < occurence; i++)
        {
            nextEventTime = distribution(generator);
            totalTime += nextEventTime;
            //cout << nextEventTime << endl;
        }
        cout << "Average next event time = " << totalTime / occurence << endl;
        return totalTime / occurence;
    }
    
    double getNextEventTime_cStyle()
    {
        double randomValue, nextTime;
        randomValue = (double) rand() / ((double) RAND_MAX + 1); // avoiding 0 because log(0) is undefined.
        nextTime = -logf(1.0 - randomValue) / lambda;
        return nextTime;
    }

    double getAverageNextEventTime_cStyle(unsigned occurence = 1000000)
    {
        double nextTime, totalTime = 0.0;
        for (unsigned i = 0; i < occurence; i++)
        {
            nextTime = getNextEventTime_cStyle();
            totalTime += nextTime;
        }
        cout << "Average next event time = " << totalTime / occurence << endl;
        return totalTime / occurence;
    }

private:
    std::default_random_engine generator;
    unsigned seed;
    double lambda;
    std::exponential_distribution<double> distribution;
};

class CheckPoint
{
public:
    void average()
    {
        vector<float> v;
        float average = accumulate( v.begin(), v.end(), 0.0) / v.size();
    }
private:
    queue<Passenger> passengers;
}

int main()
{
    cout << fixed << setprecision(2);
	cout << "Hello Project 2." << endl;
    // Passenger class.
//    Passenger p1;
//    cout << p1.getStartTime() << endl;
//    p1.setStartTime(1234);
//    cout << p1.getStartTime() << endl;
//    nextTime(1.0/40.0000);
//    cout << "Average time till next [passenger arrival]  event (over 10000 occurences) = " << getAverageNextEventTime(LAMBDA_PASSENGER_ARRIVAL, 10000)  << "  seconds." << endl;
//    cout << "Average time till next [credential station] event (over 10000 occurences) = " << getAverageNextEventTime(LAMBDA_CREDENTIAL_STATION, 10000) << "  seconds." << endl;
//    cout << "Average time till next [scanning station]   event (over 10000 occurences) = " << getAverageNextEventTime(LAMBDA_SCANNING_STATION, 10000)   << " seconds." << endl;
    //test(LAMBDA_PASSENGER_ARRIVAL);
    
    RandomEventTimeGenerator passengerArrivalTimeGenerator{ LAMBDA_PASSENGER_ARRIVAL };
    passengerArrivalTimeGenerator.getAverageNextEventTime();
    passengerArrivalTimeGenerator.getAverageNextEventTime_cStyle();
    RandomEventTimeGenerator credentialCheckTimeGenerator{ LAMBDA_CREDENTIAL_STATION };
    credentialCheckTimeGenerator.getAverageNextEventTime();
    credentialCheckTimeGenerator.getAverageNextEventTime_cStyle();
    RandomEventTimeGenerator scanningTimeGenerator{ LAMBDA_SCANNING_STATION };
    scanningTimeGenerator.getAverageNextEventTime();
    scanningTimeGenerator.getAverageNextEventTime_cStyle();
	return 0;
}
