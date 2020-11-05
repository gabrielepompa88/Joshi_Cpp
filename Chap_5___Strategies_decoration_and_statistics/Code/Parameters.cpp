#include "Parameters.h"

// Parameters definitions

// (deep) copy constructor
Parameters::Parameters(const Parameters& original)
{
	InnerObjectPtr = original.InnerObjectPtr->clone();
}

// constructor accepting Implementation object
Parameters::Parameters(const ParametersInner& innerObject)
{
	InnerObjectPtr = innerObject.clone();
}

// destructor
Parameters::~Parameters()
{
	delete InnerObjectPtr;
}

// (deep) copy assignment operator=
Parameters& Parameters::operator=(const Parameters& original)
{
	if (this != &original)
	{
		delete InnerObjectPtr;
		InnerObjectPtr = original.InnerObjectPtr->clone();
	}

	return *this;
}

// method to compute the average parameter between two times (original Interface method)
double Parameters::Mean(double time1, double time2) const
{
	return Integral(time1, time2) / (time2 - time1);
}

// method to compute the RMS parameter between two times (original Interface method)
double Parameters::RootMeanSquare(double time1, double time2) const
{
	return IntegralSquare(time1, time2) / (time2 - time1);
}

/*------------------------------------------------------------------------------------------*/

// ParametersConstant definitions

// constructor
ParametersConstant::ParametersConstant(double constant) :
	Constant{ constant }, ConstantSquare{ constant * constant }
{
}

// virtual copy constructor overriden
// returning the derived class pointer is allowed
ParametersConstant* ParametersConstant::clone() const
{
	return new ParametersConstant(*this);
}

// definite integral method
double ParametersConstant::Integral(double time1, double time2) const
{
	return Constant * (time2 - time1);
}

// definite integral of squared parameter method
double ParametersConstant::IntegralSquare(double time1, double time2) const
{
	return ConstantSquare * (time2 - time1);
}