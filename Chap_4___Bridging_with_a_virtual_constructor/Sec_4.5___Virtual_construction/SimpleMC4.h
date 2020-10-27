#ifndef SIMPLEMC4_H
#define SIMPLEMC4_H

#include "Vanilla2.h"

double SimpleMonteCarlo3(const VanillaOption& TheOption,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPath);

#endif
