#include "ConvergenceTable_unique_ptr.h"

// constructor from std::unique_ptr to non-decorated class
// Inner takes ownership of StatisticsMC resource from Inner_
ConvergenceTable::ConvergenceTable(std::unique_ptr<StatisticsMC> Inner_): Inner{ std::move(Inner_) }
{
	StoppingPoint = 2;
	PathsDone = 0;
}

// deep-copy constructor (needed to have clone() method)
ConvergenceTable::ConvergenceTable(const ConvergenceTable& original) : Inner{ original.Inner->clone() }
{
	StoppingPoint = 2;
	PathsDone = 0;
}

// virtual deep-copy constructor
StatisticsMC* ConvergenceTable::clone() const
{
	return new ConvergenceTable(*this);
}

//
// below the overriden interface methods inherited from Component
//

void ConvergenceTable::DumpOneResult(double result)
{
	Inner->DumpOneResult(result);
	++PathsDone;

	if (PathsDone == StoppingPoint)
	{
		StoppingPoint *= 2;

		std::vector<std::vector<double>> thisResult(Inner->GetResultsSoFar());
		for (unsigned long i = 0; i < thisResult.size(); i++)
		{
			thisResult[i].push_back(PathsDone);
			ResultsSoFar.push_back(thisResult[i]);
		}
	}
}

std::vector<std::vector<double>> ConvergenceTable::GetResultsSoFar() const
{
	std::vector<std::vector<double> > tmp(ResultsSoFar);
	if (PathsDone * 2 != StoppingPoint)
	{
		std::vector<std::vector<double>> thisResult(Inner->GetResultsSoFar());
		for (unsigned long i = 0; i < thisResult.size(); i++)
		{
			thisResult[i].push_back(PathsDone);
			tmp.push_back(thisResult[i]);
		}
	}

	return tmp;
}