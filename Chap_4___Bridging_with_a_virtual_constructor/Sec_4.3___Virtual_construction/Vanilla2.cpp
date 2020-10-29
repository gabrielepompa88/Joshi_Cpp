#include "Vanilla2.h"

// constructor
VanillaOption::VanillaOption(const PayOff& ThePayOff_, double Expiry_) :
	Expiry{ Expiry_ } 
{
	ThePayOffPtr = ThePayOff_.clone();
}

// Expiry getter
double VanillaOption::GetExpiry() const
{
	return Expiry;
}

// wrapper to PayOff::operator() to get payoff value
double VanillaOption::OptionPayOff(double Spot) const
{
	// alternatively:
	// return (*ThePayOffPtr)(Spot);
	return ThePayOffPtr->operator() (Spot);
}

// (deep) copy constructor
VanillaOption::VanillaOption(const VanillaOption& original)
{
	Expiry = original.GetExpiry();
	ThePayOffPtr = original.ThePayOffPtr->clone();
}

// (deep) copy assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& original)
{
	if (this != &original)
	{
		Expiry = original.GetExpiry();
		delete ThePayOffPtr;
		ThePayOffPtr = original.ThePayOffPtr->clone();
	}

	return *this;
}

// destructor
VanillaOption::~VanillaOption()
{
	delete ThePayOffPtr;
}

