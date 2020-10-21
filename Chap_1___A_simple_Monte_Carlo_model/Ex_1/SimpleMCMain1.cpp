// SimpleMCMain1.cpp
//
// Basic procedural implementation of a pricer for a vanilla call and put options.
// enum class Contract is an additional parameter to SimpleMonteCarlo1 to discriminate between calls and puts.

//require Random1.cpp

#include "Random1.h"
#include <iostream>
#include <cmath>
#include <string>

enum class Contract
{
    CALL,
    PUT
};

//function doing the MC simulation
double SimpleMonteCarlo1(double Expiry,
    double Strike,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPath,
    Contract CallOrPut)
{
    double variance{ Vol * Vol * Expiry };
    double rootVariance{ std::sqrt(variance) };
    double itoCorrection{ -0.5 * variance };

    double movedSpot{ Spot * std::exp(r * Expiry + itoCorrection) }; //compute first to reduce call exp()
    double thisSpot;
    double thisPayoff{};
    double runningSum{ 0 };

    for (unsigned long i = 0; i < NumberOfPath; i++)
    {
        double thisGaussian{ GetOneGaussianByBoxMuller() };
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        switch (CallOrPut)
        {
        case Contract::CALL:
            thisPayoff = thisSpot - Strike;
            break;
        case Contract::PUT:
            thisPayoff = Strike - thisSpot;
            break;
        default:
            throw "Unknown contract kind...";
        }
        
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }

    double mean{ runningSum / NumberOfPath };
    mean *= std::exp(-r * Expiry);
    return mean;
}

int main()
{
    Contract contractKind;
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;

    //read in parameters
    int contractSelector;
    do
    {
        std::cout << "\nKind of contract? (press 0 for 'calls', 1 for 'puts')\n";
        std::cin >> contractSelector;
    } while ((contractSelector != 0) & (contractSelector != 1));

    switch (contractSelector)
    {
    case 0:
        contractKind = Contract::CALL;
        break;
    case 1:
        contractKind = Contract::PUT;
        break;
    default:
        throw "Unknown contractSelector...";
    }

    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double result{ SimpleMonteCarlo1(Expiry,
        Strike,
        Spot,
        Vol,
        r,
        NumberOfPath,
        static_cast<Contract>(contractKind)) };
    std::cout << "the price is " << result << "\n";

    return 0;

}