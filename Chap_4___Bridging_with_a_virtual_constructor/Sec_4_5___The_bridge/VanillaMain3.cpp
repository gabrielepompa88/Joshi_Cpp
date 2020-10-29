// VanillaMain3.cpp
//
// main from Section 4.5 "Bridging with a virtual constructor" - "The bridge"
// It uses a VanillaOption class and bridge pattern to separate
// Interface part (class PayOffBridge) and Implementation part (class PayOff hierarchy)
// on the payoff side.

#include "SimpleMC5.h"
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

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    const PayOffCall thePayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption theOption(thePayOff, Expiry);

    double resultCall{ SimpleMonteCarlo3(
        theOption,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the call option is " << resultCall << "\n";

    // copy constructs VanillaOption obj, calling the (deep) copy PayOffBridge constructor
    VanillaOption secondOption(theOption);

    resultCall = SimpleMonteCarlo3(
        secondOption,
        Spot,
        Vol,
        r,
        NumberOfPath);

    std::cout << "the price of the (copy-constructed) call option is " << resultCall << "\n";

    const PayOffPut otherPayOff(Strike);

    // constructs VanillaOption obj from the PayOffBridge constructor from Implementor object
    VanillaOption thirdOption(otherPayOff, Expiry);

    // assign VanillaOption obj, calling the (deep) copy PayOffBridge assignment operator=
    theOption = thirdOption; // calling (deep) copy assignment operator

    double resultPut{ SimpleMonteCarlo3(
        theOption,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the put option is " << resultPut << "\n";

    std::cout << "Let's consider now a double-digital option: \n";
    std::cout << "\nEnter Lower Option Level\n";
    std::cin >> Low;

    std::cout << "\nEnter Upper Option Level\n";
    std::cin >> Up;

    const PayOffDoubleDigital theDoubleDigitalPayOff(Low, Up);
    VanillaOption theDigitalOption(theDoubleDigitalPayOff, Expiry); // calling standard constructor with digital-option payoff

    double resultDigital{ SimpleMonteCarlo3(
        theDigitalOption,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the double-digital option is " << resultDigital << "\n";

    return 0;

}