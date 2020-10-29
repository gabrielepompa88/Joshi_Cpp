#ifndef DOUBLEDIGITAL_H
#define DOUBLEDIGITAL_H

#include "PayOff3.h"

class PayOffDoubleDigital : public PayOff {

public:
	PayOffDoubleDigital(double LowerLevel_, double UpperLevel_);
	virtual double operator() (double Spot) const override;
	virtual ~PayOffDoubleDigital() {};

	// virtual copy constructor overriden, returning pointer to PayOffDoubleDigital derived class
	virtual PayOffDoubleDigital* clone() const override;

private:
	double UpperLevel;
	double LowerLevel;
};

#endif