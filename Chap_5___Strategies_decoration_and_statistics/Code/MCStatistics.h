#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class StatisticsMC // abstract statistics gatherer
{
public:

	StatisticsMC() {}

	// (pure) virtual method to retrieve data and update statistics
	virtual void DumpOneResult(double result) = 0;

	// (pure) virtual method to output the statistics
	virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;

	// (pure) virtual copy constructor
	virtual StatisticsMC* clone() const = 0;

	// virtual destructor
	virtual ~StatisticsMC() {}
};

class StatisticsMean : public StatisticsMC
{
public:

	StatisticsMean();

	// virtual method to retrieve data and update statistics
	virtual void DumpOneResult(double result) override;

	// virtual method to output the statistics
	virtual std::vector<std::vector<double>> GetResultsSoFar() const override;

	// virtual copy constructor
	virtual StatisticsMean* clone() const override;

private:

	double RunningSum;
	unsigned long PathsDone;
};

#endif
