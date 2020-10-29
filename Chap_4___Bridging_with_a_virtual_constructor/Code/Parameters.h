#ifndef PARAMETERS_H
#define PARAMETERS_H

// Bridge design pattern applied to parameter classes

class ParametersInner // Implementation interface
{
public:

	// constructor
	ParametersInner() {}

	// virtual copy constructor
	virtual ParametersInner* clone() const = 0;

	// destructor
	virtual ~ParametersInner() {}

	// definite integral method (pure virtual method)
	virtual double Integral(double time1, double time2) const = 0;

	// definite integral of squared parameter method (pure virtual method)
	virtual double IntegralSquare(double time1, double time2) const = 0;

};

class Parameters // Interface 
{

private:

	ParametersInner* InnerObjectPtr{}; // link to the Implementation part

public:

	// (deep) copy constructor
	Parameters(const Parameters& original);

	// constructor accepting Implementation object
	Parameters(const ParametersInner& innerObject);

	// (deep) copy assignment operator=
	Parameters& operator=(const Parameters& original);

	// destructor
	virtual ~Parameters();

	// definite integral method (delegated to Implementation)
	double Integral(double time1, double time2) const
	{
		return InnerObjectPtr->Integral(time1, time2);
	}

	// definite integral of squared parameter method
	double IntegralSquare(double time1, double time2) const
	{
		return InnerObjectPtr->IntegralSquare(time1, time2);
	}

	// method to compute the average parameter between two times (original Interface method)
	double Mean(double time1, double time2) const;

	// method to compute the RMS parameter between two times (original Interface method)
	double RootMeanSquare(double time1, double time2) const;
};

class ParametersConstant : public ParametersInner // a concrete Implementor
{
private:

	double Constant{};
	double ConstantSquare{};

public:

	// constructor
	ParametersConstant(double constant);

	// virtual copy constructor overriden
	// returning the derived class pointer is allowed
	virtual ParametersConstant* clone() const override;

	// destructor
	virtual ~ParametersConstant() {};

	// definite integral method
	virtual double Integral(double time1, double time2) const override;

	// definite integral of squared parameter method
	virtual double IntegralSquare(double time1, double time2) const override;
};
#endif
