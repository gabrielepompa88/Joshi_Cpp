#include "PayOff1.h"
#include <algorithm>

PayOff::PayOff(double Strike_, OptionType TheOptionsType_) :
    Strike{ Strike_ }, TheOptionsType{ TheOptionsType_ }
{
}

// digital cases included
double PayOff::operator() (double Spot) const
{
    switch (TheOptionsType)
    {
    case OptionType::call:
        return std::max(Spot - Strike, 0.0);
        break;
    case OptionType::put:
        return std::max(Strike - Spot, 0.0);
        break;
    case OptionType::callDigital:
        return (Strike >= Spot ? 1.0 : 0.0);
        break;
    case OptionType::putDigital:
        return (Strike >= Spot ? 0.0 : 1.0);
        break;
    default:
        throw "Unknown option type found...";
    }

}