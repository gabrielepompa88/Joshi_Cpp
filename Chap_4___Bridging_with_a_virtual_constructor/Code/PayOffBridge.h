#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include "PayOff3.h"

// The class PayOffBridge is the Interface class bridging with the Implementation PayOff

class PayOffBridge
{

public:

	// (deep) copy constructor
	PayOffBridge(const PayOffBridge& original);

	// constructor from Implementor object
	PayOffBridge(const PayOff& innerPayOff);

	// (deep) copy assignment operator
	PayOffBridge& operator=(const PayOffBridge& original);

	// destructor
	~PayOffBridge();

	// wrapper to Implementation operator() to get payoff value
	double operator() (double Spot) const;

private:

	PayOff* ThePayOffPtr; // link to the Implementor

};
#endif // !PAYOFFBRIDGE_H
