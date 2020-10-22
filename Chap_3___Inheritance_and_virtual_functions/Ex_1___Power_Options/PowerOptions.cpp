#include "PowerOptions.h"
#include <algorithm>
#include <cmath>

PayOffCallPowerOption::PayOffCallPowerOption(double Strike_, int Power_) :
    Strike{ Strike_ }, Power{ Power_ }
{
}

double PayOffCallPowerOption::operator() (double Spot) const
{
    return std::max(std::pow(Spot, Power) - Strike, 0.0);
}

PayOffPutPowerOption::PayOffPutPowerOption(double Strike_, int Power_) :
    Strike{ Strike_ }, Power{ Power_ }
{
}

double PayOffPutPowerOption::operator() (double Spot) const
{
    return std::max(Strike - std::pow(Spot, Power), 0.0);
}