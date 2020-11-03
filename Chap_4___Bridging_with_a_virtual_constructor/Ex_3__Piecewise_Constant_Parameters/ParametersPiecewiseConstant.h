#ifndef PARAMETERSPIECEWISECONSTANT_H
#define PARAMETERSPIECEWISECONSTANT_H

// ParametersPiecewiseConstant class implements:
//
// (T_type time, V_type value) pairs:
//
// value_0 for [0,T_0]
// value_1 for [T_0,T_1]
// ...
// value_i for [T_{i-1},T_i]
// ...
//

#include "Parameters.h"
#include <vector>
#include <utility> // for std::pair, std::make_pair
#include <ostream>

template<class T_type, class V_type>
class ParametersPiecewiseConstant : public ParametersInner // another concrete Implementor
{
private:

	std::vector<std::pair<T_type, V_type>> Constant{};
	std::vector<std::pair<T_type, V_type>> ConstantSquare{};
	int piecesNum{};

public:

	// constructor
	ParametersPiecewiseConstant(std::vector<std::pair<T_type, V_type>> constant);

	// virtual copy constructor overriden
	// returning the derived class pointer is allowed
	virtual ParametersPiecewiseConstant* clone() const override;

	// destructor
	virtual ~ParametersPiecewiseConstant() {};

	// definite integral method
	virtual double Integral(double time1, double time2) const override;

	// definite integral of squared parameter method
	virtual double IntegralSquare(double time1, double time2) const override;

	// overloaded operator<<
	// using the Approach #1 here: https://web.mst.edu/~nmjxv3/articles/templates.html
	// See also here: https://stackoverflow.com/a/8813413/2533366
	// Note different template parameters <T,V> instead of <class T_type, class V_type>
	template<class T, class V>
	friend std::ostream& operator<<(std::ostream& out, const ParametersPiecewiseConstant<T, V>& param);
	
	/*
	// alternatively, a seperate - non-template operator<< can be generated for each <T_type, V_type>
	// pair, as a friend of ParametersPiecewiseConstant<T_type, V_type>
	// as shown in the first solution here: https://en.cppreference.com/w/cpp/language/friend
	friend std::ostream& operator<<(std::ostream& out, const ParametersPiecewiseConstant& param)
	{
		for (const auto& x : param.Constant)
		{
			out << "(time=" << x.first << ", value=" << x.second << ")\n";
		}

		return out;
	}
	*/
};	

/*------------------------------------------------------------------------------------------*/

// ParametersPiecewiseConstant definitions

// constructor
template<class T_type, class V_type>
ParametersPiecewiseConstant<T_type, V_type>::ParametersPiecewiseConstant(std::vector<std::pair<T_type, V_type>> constant):
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
template<class T_type, class V_type>
ParametersPiecewiseConstant<T_type,V_type>* ParametersPiecewiseConstant<T_type,V_type>::clone() const
{
	return new ParametersPiecewiseConstant(*this);
}

// definite integral method
template<class T_type, class V_type>
double ParametersPiecewiseConstant<T_type, V_type>::Integral(double time1, double time2) const
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
template<class T_type, class V_type>
double ParametersPiecewiseConstant<T_type, V_type>::IntegralSquare(double time1, double time2) const
{
	double integralValue{ ConstantSquare[0].second * ConstantSquare[0].first }; // I(0,T) = (C_0)^2 * T

	for (int i = 1; i < piecesNum; i++)
	{
		// I(T_i,T_{i-1}) = (C_i)^2 * (T_i - T_{i-1})
		integralValue += ConstantSquare[i].second * (ConstantSquare[i].first - ConstantSquare[i - 1].first);
	}

	return integralValue;
}


// overloaded operator<<
template<class T_type, class V_type>
std::ostream& operator<< (std::ostream& out, const ParametersPiecewiseConstant<T_type, V_type>& param)
{
	for(const auto &x: param.Constant)
	{
		out << "(time="<< x.first << ", value=" << x.second<<")\n";
	}

	return out;
}

#endif