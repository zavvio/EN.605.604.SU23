#include "RandomEventTimeGenerator.h"

RandomEventTimeGenerator::RandomEventTimeGenerator(double lambda) :
    lambda{ lambda },
    distribution{ lambda },
    seed{ (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count() }
{
    generator.seed(seed);

#ifdef EXPERIMENTAL
    // C Style - seed random number generator
    srand((unsigned)time(NULL));
#endif
}

double RandomEventTimeGenerator::getNextEventTime()
{
    return distribution(generator);;
}

#ifdef EXPERIMENTAL
double RandomEventTimeGenerator::getAverageNextEventTime(unsigned occurence)
{
    double nextEventTime, totalTime = 0.0;
    for (unsigned i = 0; i < occurence; i++)
    {
        nextEventTime = distribution(generator);
        totalTime += nextEventTime;
        //cout << nextEventTime << endl;
    }
    std::cout << "Average next event time = " << totalTime / occurence << std::endl;
    return totalTime / occurence;
}

double RandomEventTimeGenerator::getNextEventTime_cStyle()
{
    double randomValue, nextTime;
    randomValue = (double)rand() / ((double)RAND_MAX + 1); // avoiding 0 because log(0) is undefined.
    nextTime = (double)-logf((float)(1.0 - randomValue)) / lambda;
    return nextTime;
}

double RandomEventTimeGenerator::getAverageNextEventTime_cStyle(unsigned occurence)
{
    double nextTime, totalTime = 0.0;
    for (unsigned i = 0; i < occurence; i++)
    {
        nextTime = getNextEventTime_cStyle();
        totalTime += nextTime;
    }
    std::cout << "Average next event time = " << totalTime / occurence << std::endl;
    return totalTime / occurence;
}
#endif