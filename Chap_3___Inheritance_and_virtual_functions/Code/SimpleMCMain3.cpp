// SimpleMCMain3.cpp
//
// main from Chap 3 "Inheritance and virtual functions": inherits PayOffCall and PayOffPut publicly from PayOff.

#include "SimpleMC2.h"
#include <iostream>

int main()
{
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;

    //read in parameters
    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    const PayOffCall callPayOff(Strike);
    const PayOffPut putPayOff(Strike);

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double resultCall{ SimpleMonteCarlo2(
        callPayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    double resultPut{ SimpleMonteCarlo2(
        putPayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the call option is " << resultCall << "\n";
    std::cout << "the price of the put option is " << resultPut << "\n";

    return 0;

}