// StatsMain2_unique_ptr.cpp
//
// ConvergenceTable class uses (composition) a std::unique_ptr to link to StatisticsMC hierarchy.
// No Wrapper class is used.

#include "SimpleMC7.h"
#include "Parameters.h"
#include "Vanilla3.h"
#include "DoubleDigital2.h"
#include "MCStatistics.h" // for StatisticMean class
#include "ConvergenceTable_unique_ptr.h" // for ConvergenceTable class
#include <iostream>

// auxiliary function to print output
template<class T>
void printOutput(const std::vector<std::vector<T>> &theResults)
{
    // loop to output results
    for (const std::vector<T>& vec : theResults)
    {
        for (const T& res : vec)
        {
            std::cout << res << " ";
        }

        std::cout << "\n";
    }
}

int main()
{
    double Expiry;
    double Strike;
    double Low;
    double Up;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;

    //read in parameters
    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    // volatility parameter as ParametersConstant object
    ParametersConstant VolParam{ Vol };

    std::cout << "\nEnter r\n";
    std::cin >> r;

    // short-rate parameter as ParametersConstant object
    ParametersConstant rParam{ r };

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    const PayOffCall thePayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption theOption(thePayOff, Expiry);

    /* ORIGINAL:
     
    // statistics gatherer
    StatisticsMean gathererCall;

    // convergence table
    ConvergenceTable gathererTableCall{ gathererCall };

    */

    // convergence table initialized with a std::unique_ptr in input
    ConvergenceTable gathererTableCall{ std::make_unique<StatisticsMean>()};

    SimpleMonteCarlo5(
        theOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath,
        gathererTableCall); // non-decorated gathererCall would work as well

    // output results (vector of vectors)
    // non-decorated gathererCall would work as well
    std::cout << "For the price of the call option the results are \n";
    printOutput(gathererTableCall.GetResultsSoFar());

    // copy constructs VanillaOption obj, calling the (deep) copy PayOffBridge constructor
    VanillaOption secondOption(theOption);

    /* ORIGINAL:
     
    // statistics gatherer
    StatisticsMean gathererCall2;

    // convergence table
    ConvergenceTable gathererTableCall2{ gathererCall2 };

    */

    // convergence table initialized with a std::unique_ptr in input
    ConvergenceTable gathererTableCall2{ std::make_unique<StatisticsMean>() };

    SimpleMonteCarlo5(
        secondOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath,
        gathererTableCall2); // non-decorated gathererCall2 would work as well

    // output results (vector of vectors)
    // non-decorated gathererCall2 would work as well
    std::cout << "For the price of the (copy-constructed) call option the results are \n";
    printOutput(gathererTableCall2.GetResultsSoFar());

    const PayOffPut otherPayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption thirdOption(otherPayOff, Expiry);

    // assign VanillaOption obj, calling the (deep) copy PayOffBridge assignment operator=
    theOption = thirdOption; // calling (deep) copy assignment operator

    /* ORIGINAL:
    
    // statistics gatherer
    StatisticsMean gathererPut;

    // convergence table
    ConvergenceTable gathererTablePut{ gathererPut };

    */

    // convergence table initialized with a std::unique_ptr in input
    ConvergenceTable gathererTablePut{ std::make_unique<StatisticsMean>() };

    SimpleMonteCarlo5(
        theOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath,
        gathererTablePut); // non-decorated gathererPut would work as well

    // output results (vector of vectors)
    // non-decorated gathererPut would work as well
    std::cout << "For the price of the put option the results are \n";
    printOutput(gathererTablePut.GetResultsSoFar());

    std::cout << "Let's consider now a double-digital option: \n";
    std::cout << "\nEnter Lower Option Level\n";
    std::cin >> Low;

    std::cout << "\nEnter Upper Option Level\n";
    std::cin >> Up;

    const PayOffDoubleDigital theDoubleDigitalPayOff(Low, Up);
    VanillaOption theDigitalOption(theDoubleDigitalPayOff, Expiry); // calling standard constructor with digital-option payoff

    /*  ORIGINAL:
    
    // statistics gatherer
    StatisticsMean gathererDoubleDigital;

    // convergence table
    ConvergenceTable gathererTableDoubleDigital{ gathererDoubleDigital };

    */

    // convergence table initialized with a std::unique_ptr in input
    ConvergenceTable gathererTableDoubleDigital{ std::make_unique<StatisticsMean>() };

    SimpleMonteCarlo5(
        theDigitalOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath,
        gathererTableDoubleDigital); // non-decorated gathererDoubleDigital would work as well

    // output results (vector of vectors)
    // non-decorated gathererDoubleDigital would work as well
    std::cout << "For the price of the double-digital option the results are \n";
    printOutput(gathererTableDoubleDigital.GetResultsSoFar());

    return 0;

}