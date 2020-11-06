#ifndef CONVERGENCE_TABLE_UNIQUE_PTR_H
#define CONVERGENCE_TABLE_UNIQUE_PTR_H

#include "MCStatistics.h"
#include <memory> // for std::unique_ptr and std::make_unique

// Example of Decorator pattern: the ConvergenceTable Decorator decorates the StatisticsMC Content
// See: https://en.wikipedia.org/wiki/Decorator_pattern

class ConvergenceTable : public StatisticsMC
{
public:

	// constructor from std::unique_ptr to non-decorated class
	ConvergenceTable(std::unique_ptr<StatisticsMC> Inner_);
	
	// additional copy constructor
	ConvergenceTable(const ConvergenceTable& original);

	// ovverriden virtual deep-copy constructor
	virtual StatisticsMC* clone() const override;

	// overriden interface methods inherited from Component
	virtual void DumpOneResult(double result) override;
	virtual std::vector<std::vector<double>>GetResultsSoFar() const override;

private:

	// pointer to Component
	std::unique_ptr<StatisticsMC> Inner;

	std::vector<std::vector<double>> ResultsSoFar;
	unsigned long StoppingPoint;
	unsigned long PathsDone;
};

#endif