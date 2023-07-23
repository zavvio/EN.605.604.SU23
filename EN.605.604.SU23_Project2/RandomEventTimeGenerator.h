#pragma once
#include <chrono>
#include <random>
#include "DevUtil.h"

class RandomEventTimeGenerator
{
public:
    RandomEventTimeGenerator() = delete;
    RandomEventTimeGenerator(double lambda);

    double getNextEventTime();

#ifdef EXPERIMENTAL
    double getAverageNextEventTime(unsigned occurence = 1000000);
    double getNextEventTime_cStyle();
    double getAverageNextEventTime_cStyle(unsigned occurence = 1000000);
#endif

private:
    std::default_random_engine generator;
    unsigned seed;
    double lambda;
    std::exponential_distribution<double> distribution;
};