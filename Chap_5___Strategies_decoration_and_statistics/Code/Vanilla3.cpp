#include "Vanilla3.h"

// constructor
VanillaOption::VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_) :
	ThePayOff{ ThePayOff_ }, Expiry{ Expiry_ }
{
}

// Expiry getter
double VanillaOption::GetExpiry() const
{
	return Expiry;
}

// wrapper to PayOffBridge::operator() to get payoff value
double VanillaOption::OptionPayOff(double Spot) const
{
	return ThePayOff(Spot);
}