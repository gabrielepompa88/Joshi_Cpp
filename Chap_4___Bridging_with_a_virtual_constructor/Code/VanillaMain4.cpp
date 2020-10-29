// VanillaMain4.cpp
//
// main from Chapter 4 "Bridging with a virtual constructor"
// It uses a VanillaOption class and bridge pattern applied to:
// - payoff: PayOffBridge (Interface) / PayOff (base of Implementation hierarchy)
// - parameters: Parameters (Interface) / ParametersInner (base of Implementation hierarchy)

#include "SimpleMC6.h"
#include "Parameters.h"
#include "Vanilla3.h"
#include "DoubleDigital2.h"
#include <iostream>

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