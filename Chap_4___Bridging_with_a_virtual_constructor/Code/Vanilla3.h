#ifndef VANILLA_3_H
#define VANILLA_3_H

#include "PayOffBridge.h"

class VanillaOption
{

public:

	// constructor
	VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_);

	// Expiry getter
	double GetExpiry() const;

	// wrapper to PayOffBridge::operator() to get payoff value
	double OptionPayOff(double Spot) const;

private:

	double Expiry;
	PayOffBridge ThePayOff; // Interface object (part of the PayOffBrdige/PayOff bridge)

};
#endif // !VANILLA_3_H
