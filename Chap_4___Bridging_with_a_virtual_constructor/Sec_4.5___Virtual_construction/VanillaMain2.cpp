// SimpleMCMain3.cpp
//
// main from Section 4.3 "Bridging with a virtual constructor" - "virtual constructor"
// It uses a VanillaOption class, using a virtually copy-constructed PayOff class.
// VanillaOption manages the memory for the PayOff class.

#include "SimpleMC4.h"
#include "Vanilla2.h"
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
    VanillaOption theOption(thePayOff, Expiry); // calling standard constructor

    double resultCall{ SimpleMonteCarlo3(
        theOption,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the call option is " << resultCall << "\n";

    VanillaOption secondOption(theOption); // calling (deep) copy constructor

    resultCall = SimpleMonteCarlo3(
        secondOption,
        Spot,
        Vol,
        r,
        NumberOfPath) ;

    std::cout << "the price of the (copy-constructed) call option is " << resultCall << "\n";

    const PayOffPut otherPayOff(Strike);
    VanillaOption thirdOption(otherPayOff, Expiry); // calling standard constructor
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