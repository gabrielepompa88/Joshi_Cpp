#ifndef PAYOFF3_H
#define PAYOFF3_H

class PayOff {

public:

	PayOff() {};
	virtual double operator() (double Spot) const = 0;
	virtual ~PayOff() {};

	// virtual copy constructor, returning pointer to PayOff base class 
	virtual PayOff* clone() const = 0;

};

class PayOffCall : public PayOff {

public:
	PayOffCall(double Strike_);
	virtual double operator() (double Spot) const override;
	virtual ~PayOffCall() {};

	// virtual copy constructor overriden, returning pointer to PayOffCall derived class
	virtual PayOffCall* clone() const override;

private:
	double Strike;
};

class PayOffPut : public PayOff {

public:
	PayOffPut(double Strike_);
	virtual double operator() (double Spot) const override;
	virtual ~PayOffPut() {};

	// virtual copy constructor overriden, returning pointer to PayOffPut derived class
	virtual PayOffPut* clone() const override;

private:
	double Strike;
};

#endif