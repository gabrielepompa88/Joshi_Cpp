#ifndef CONVERGENCE_TABLE_H
#define CONVERGENCE_TABLE_H

#include "MCStatistics.h"
#include "wrapper.h"

// Example of Decorator pattern: the ConvergenceTable Decorator decorates the StatisticsMC Content
// See: https://en.wikipedia.org/wiki/Decorator_pattern

class ConvergenceTable : public StatisticsMC
{
public:

	// constructor from (wrapper of) non-decorated class
	ConvergenceTable(const Wrapper<StatisticsMC>& Inner_);
	
	// ovverriden virtual deep-copy constructor
	virtual StatisticsMC* clone() const override;

	// overriden interface methods inherited from Component
	virtual void DumpOneResult(double result) override;
	virtual std::vector<std::vector<double>>GetResultsSoFar() const override;

private:

	// pointer to Component
	Wrapper<StatisticsMC> Inner;

	std::vector<std::vector<double>> ResultsSoFar;
	unsigned long StoppingPoint;
	unsigned long PathsDone;
};

#endif