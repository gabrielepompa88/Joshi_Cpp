#ifndef PARAMETERSPIECEWISECONSTANT_H
#define PARAMETERSPIECEWISECONSTANT_H

#include "Parameters.h"
#include <vector>
#include <utility> // for std::pair, std::make_pair

template<class T1, class T2>
class ParametersPiecewiseConstant : public ParametersInner // another concrete Implementor
{
private:

	// (time, value) pairs:
	//
	// value_0 for [0,T_0]
	// value_1 for [T_0,T_1]
	// ...
	// value_i for [T_{i-1},T_i]
	// ...
	//
	std::vector<std::pair<T1, T2>> Constant{};
	std::vector<std::pair<T1, T2>> ConstantSquare{};
	int piecesNum{};

public:

	// constructor
	ParametersPiecewiseConstant(std::vector<std::pair<T1, T2>> constant);

	// virtual copy constructor overriden
	// returning the derived class pointer is allowed
	virtual ParametersPiecewiseConstant* clone() const override;

	// destructor
	virtual ~ParametersPiecewiseConstant() {};

	// definite integral method
	virtual double Integral(double time1, double time2) const override;

	// definite integral of squared parameter method
	virtual double IntegralSquare(double time1, double time2) const override;

};

/*------------------------------------------------------------------------------------------*/

// ParametersPiecewiseConstant definitions

// constructor
template<class T1, class T2>
ParametersPiecewiseConstant<T1, T2>::ParametersPiecewiseConstant(std::vector<std::pair<T1, T2>> constant):
	Constant(constant)
{
	piecesNum = Constant.size() ;

	// ConstantSquare build from Constant, leaving times untouched and squaring values
	for (int i = 0; i < piecesNum; i++)
	{
		ConstantSquare.push_back(std::make_pair(Constant[i].first, Constant[i].second * Constant[i].second));
	}
}

// virtual copy constructor overriden
// returning the derived class pointer is allowed
template<class T1, class T2>
ParametersPiecewiseConstant<T1,T2>* ParametersPiecewiseConstant<T1,T2>::clone() const
{
	return new ParametersPiecewiseConstant(*this);
}

// definite integral method
template<class T1, class T2>
double ParametersPiecewiseConstant<T1, T2>::Integral(double time1, double time2) const
{
	double integralValue{Constant[0].second * Constant[0].first}; // I(0,T) = C_0 * T

	for (int i = 1; i < piecesNum; i++)
	{
		// I(T_i,T_{i-1}) = C_i * (T_i - T_{i-1})
		integralValue += Constant[i].second * (Constant[i].first - Constant[i-1].first);
	}

	return integralValue;
}

// definite integral of squared parameter method
template<class T1, class T2>
double ParametersPiecewiseConstant<T1, T2>::IntegralSquare(double time1, double time2) const
{
	double integralValue{ ConstantSquare[0].second * ConstantSquare[0].first }; // I(0,T) = (C_0)^2 * T

	for (int i = 1; i < piecesNum; i++)
	{
		// I(T_i,T_{i-1}) = (C_i)^2 * (T_i - T_{i-1})
		integralValue += ConstantSquare[i].second * (ConstantSquare[i].first - ConstantSquare[i - 1].first);
	}

	return integralValue;
}

#endif