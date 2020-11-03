// VanillaMain4_piecewise_constant_parameters.cpp
//
// exercise 4.3 implementing ParametersPiecewiseConstant interest rate

#include "SimpleMC6.h"
#include "Parameters.h"
#include "ParametersPiecewiseConstant.h"
#include "Vanilla3.h"
#include "DoubleDigital2.h"
#include <iostream>
#include <vector>
#include <utility> // for std::pair, std::make_pair

int main()
{
    double Expiry;
    double Strike;
    double Low;
    double Up;
    double Spot;
    double Vol;
    int N; // interval of piecewise constantess of short-rate
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

    std::cout << "\nEnter how many intervals [T_i,T_j] you want\n";
    std::cin >> N;

    // short-rate as vector of (time, value) pairs
    std::vector<std::pair<double, double>> r{};

    double r_piece{};
    double T_piece{ Expiry / N };

    for (int i = 0; i < N; i++)
    {
        std::cout << "\nEnter r in interval i = " << i << "\n";
        std::cin >> r_piece;

        r.push_back(std::make_pair(T_piece * (i+1), r_piece));
    }

    // short-rate parameter as ParametersPiecewiseConstant object
    ParametersPiecewiseConstant<double,double> rParam{ r };
    std::cout << "\nthe short-rate is:\n";
    std::cout << rParam; // calling overloaded operator<<

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    const PayOffCall thePayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption theOption(thePayOff, Expiry);

    double resultCall{ SimpleMonteCarlo4(
        theOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath) };

    std::cout << "the price of the call option is " << resultCall << "\n";

    // copy constructs VanillaOption obj, calling the (deep) copy PayOffBridge constructor
    VanillaOption secondOption(theOption);

    resultCall = SimpleMonteCarlo4(
        secondOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath);

    std::cout << "the price of the (copy-constructed) call option is " << resultCall << "\n";

    const PayOffPut otherPayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption thirdOption(otherPayOff, Expiry);

    // assign VanillaOption obj, calling the (deep) copy PayOffBridge assignment operator=
    theOption = thirdOption; // calling (deep) copy assignment operator

    double resultPut{ SimpleMonteCarlo4(
        theOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath) };

    std::cout << "the price of the put option is " << resultPut << "\n";

    std::cout << "Let's consider now a double-digital option: \n";
    std::cout << "\nEnter Lower Option Level\n";
    std::cin >> Low;

    std::cout << "\nEnter Upper Option Level\n";
    std::cin >> Up;

    const PayOffDoubleDigital theDoubleDigitalPayOff(Low, Up);
    VanillaOption theDigitalOption(theDoubleDigitalPayOff, Expiry); // calling standard constructor with digital-option payoff

    double resultDigital{ SimpleMonteCarlo4(
        theDigitalOption,
        Spot,
        VolParam,
        rParam,
        NumberOfPath) };

    std::cout << "the price of the double-digital option is " << resultDigital << "\n";

    return 0;

}