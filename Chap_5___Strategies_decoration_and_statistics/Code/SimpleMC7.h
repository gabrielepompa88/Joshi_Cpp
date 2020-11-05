#ifndef SIMPLEMC7_H
#define SIMPLEMC7_H

#include "Vanilla3.h"
#include "Parameters.h"
#include "MCStatistics.h"

void SimpleMonteCarlo5(const VanillaOption& TheOption,
    double Spot,
    const Parameters& Vol,
    const Parameters& r,
    unsigned long NumberOfPath,
    StatisticsMC& gatherer);

#endif
