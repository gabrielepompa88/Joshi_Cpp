#ifndef POWEROPTIONS_H
#define POWEROPTIONS_H

#include "PayOff2.h"

class PayOffCallPowerOption: public PayOff {

public:
	PayOffCallPowerOption(double Strike_, int Power_);
	virtual double operator() (double Spot) const;
	virtual ~PayOffCallPowerOption() {};

private:
	double Strike;
	int Power;
};

class PayOffPutPowerOption : public PayOff {

public:
	PayOffPutPowerOption(double Strike_, int Power_);
	virtual double operator() (double Spot) const;
	virtual ~PayOffPutPowerOption() {};

private:
	double Strike;
	int Power;
};

#endif