#include "DoubleDigital2.h"

PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_, double UpperLevel_) :
    LowerLevel{ LowerLevel_ }, UpperLevel{ UpperLevel_ }
{
}

double PayOffDoubleDigital::operator() (double Spot) const
{
    if ((Spot <= LowerLevel) || (Spot >= UpperLevel)) 
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

PayOffDoubleDigital* PayOffDoubleDigital::clone() const
{
    return new PayOffDoubleDigital(*this);
}
