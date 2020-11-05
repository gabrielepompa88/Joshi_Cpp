#include "MCStatistics.h"

StatisticsMean::StatisticsMean() :
	RunningSum(0.0), PathsDone(0)
{
}

// virtual method to retrieve data and update statistics
void StatisticsMean::DumpOneResult(double result)
{
	PathsDone++;
	RunningSum += result;
}

// virtual method to output the statistics
std::vector<std::vector<double>> StatisticsMean::GetResultsSoFar() const
{
	std::vector<std::vector<double>> Results(1);

	Results[0].resize(1);
	Results[0][0] = RunningSum / PathsDone;

	return Results;
}

// virtual copy constructor
StatisticsMean* StatisticsMean::clone() const
{
	return new StatisticsMean(*this);
}
