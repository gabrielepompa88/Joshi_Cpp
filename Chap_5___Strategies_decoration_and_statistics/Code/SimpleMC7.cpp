#include "SimpleMC7.h"
#include "Random1.h"
#include <cmath>

// MC using StatisticsMC class statistics gatherer (Strategy pattern implemented)

void SimpleMonteCarlo5(const VanillaOption& TheOption,
    double Spot,
    const Parameters& Vol,
    const Parameters& r,
    unsigned long NumberOfPath,
    StatisticsMC& gatherer)
{
    double Expiry{ TheOption.GetExpiry() }; // calling VanillaOption Expiry getter
    double variance{ Vol.IntegralSquare(0.0,Expiry) };
    double rootVariance{ std::sqrt(variance) };
    double itoCorrection{ -0.5 * variance };

    double movedSpot{ Spot * std::exp(r.Integral(0.0,Expiry) + itoCorrection) }; //compute first to reduce call exp()
    double thisSpot;
    // not needed: double runningSum{ 0 };
    double discounting{ std::exp(-r.Integral(0.0, Expiry)) };

    for (unsigned long i = 0; i < NumberOfPath; i++)
    {
        double thisGaussian{ GetOneGaussianByBoxMuller() };
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayoff{ TheOption.OptionPayOff(thisSpot) }; // calling VanillaOption wrapper to PayOff::operator()
        gatherer.DumpOneResult(thisPayoff * discounting); // it was: runningSum += thisPayoff;
    }

    // code below is delegated to gatherer.GetResultsSoFar()
    //
    // double mean{ runningSum / NumberOfPath };
    // mean *= std::exp(-r.Integral(0.0,Expiry));
    // return mean;
}
