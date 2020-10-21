#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff {

public:

	enum class OptionType { call, put, callDigital, putDigital }; // OptionType includes digitals
	PayOff(double Strike_, OptionType TheOptionsType_);
	double operator() (double Spot) const;

private:
	double Strike;
	OptionType TheOptionsType;

};
#endif