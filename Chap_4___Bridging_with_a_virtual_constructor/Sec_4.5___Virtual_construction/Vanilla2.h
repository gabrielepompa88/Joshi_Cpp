#ifndef VANILLA_2_H
#define VANILLA_2_H

#include "PayOff3.h"

class VanillaOption
{

public:

	// constructor
	VanillaOption(const PayOff& ThePayOff_, double Expiry_);

	// (deep) copy constructor
	VanillaOption(const VanillaOption& original);

	// (deep) copy assignment operator
	VanillaOption& operator=(const VanillaOption& original);

	// destructor
	~VanillaOption();

	// Expiry getter
	double GetExpiry() const;

	// wrapper to PayOff::operator() to get payoff value
	double OptionPayOff(double Spot) const;

private:

	double Expiry;
	PayOff* ThePayOffPtr;

};
#endif // !VANILLA_2_H
