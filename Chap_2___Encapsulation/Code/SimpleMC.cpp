#include "SimpleMC.h"
#include "Random1.h"
#include <cmath>

double SimpleMonteCarlo2(const PayOff& thePayOff,
    double Expiry,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPath)
{
    double variance{ Vol * Vol * Expiry };
    double rootVariance{ std::sqrt(variance) };
    double itoCorrection{ -0.5 * variance };

    double movedSpot{ Spot * std::exp(r * Expiry + itoCorrection) }; //compute first to reduce call exp()
    double thisSpot;
    //double thisPayoff{};
    double runningSum{ 0 };

    for (unsigned long i = 0; i < NumberOfPath; i++)
    {
        double thisGaussian{ GetOneGaussianByBoxMuller() };
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayoff{ thePayOff(thisSpot) }; // calling PayOff functor
        runningSum += thisPayoff;
    }

    double mean{ runningSum / NumberOfPath };
    mean *= std::exp(-r * Expiry);
    return mean;
}
