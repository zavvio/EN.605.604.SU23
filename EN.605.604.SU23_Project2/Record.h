#pragma once
#include "DevUtil.h"

struct Record
{
    unsigned simulatedDays{ 0 };
    unsigned passengerCount{ 0 };
    double totalQueue1Time{ 0.0 };
    double totalStation1Time{ 0.0 };
    double totalQueue2Time{ 0.0 };
    double totalStation2Time{ 0.0 };
};