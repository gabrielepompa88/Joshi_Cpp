#include "PayOffBridge.h"

// (deep) copy constructor
PayOffBridge::PayOffBridge(const PayOffBridge& original)
{
	ThePayOffPtr = original.ThePayOffPtr->clone();
}

// constructor from Implementor object
PayOffBridge::PayOffBridge(const PayOff& innerPayOff)
{
	ThePayOffPtr = innerPayOff.clone();
}

// (deep) copy assignment operator
PayOffBridge& PayOffBridge::operator=(const PayOffBridge& original)
{
	if (this != &original)
	{
		delete ThePayOffPtr;
		ThePayOffPtr = original.ThePayOffPtr->clone();
	}

	return *this;
}

// destructor
PayOffBridge::~PayOffBridge()
{
	delete ThePayOffPtr;
}

// wrapper to Implementation operator() to get payoff value
double PayOffBridge::operator() (double Spot) const
{
	// alternatively:
	// return (*ThePayOffPtr)(Spot);
	return ThePayOffPtr->operator() (Spot);
}