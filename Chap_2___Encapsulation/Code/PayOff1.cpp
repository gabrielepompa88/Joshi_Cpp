#include "PayOff1.h"
#include <algorithm>

PayOff::PayOff(double Strike_, OptionType TheOptionsType_):
	Strike{ Strike_ }, TheOptionsType{ TheOptionsType_ }
{
}

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
    default:
        throw "Unknown option type found...";
    }

}