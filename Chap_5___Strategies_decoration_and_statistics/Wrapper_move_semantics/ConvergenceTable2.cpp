#include "ConvergenceTable2.h" // only difference from Code/ConvergenceTable.cpp

// constructor from (wrapper of) non-decorated class
ConvergenceTable::ConvergenceTable(const Wrapper<StatisticsMC>& Inner_) : Inner(Inner_)
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