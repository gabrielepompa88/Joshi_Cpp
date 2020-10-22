// SimpleMCMain3.cpp
//
// main from Chap 3 "Inheritance and virtual functions": inherits PayOffCall and PayOffPut publicly from PayOff.

#include "SimpleMC2.h"
#include "DoubleDigital.h"
#include <iostream>

int main()
{
    double Expiry;
    double Low;
    double Up;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;

    //read in parameters
    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Lower Option Level\n";
    std::cin >> Low;

    std::cout << "\nEnter Upper Option Level\n";
    std::cin >> Up;

    const PayOffDoubleDigital thePayOff(Low, Up);

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double result{ SimpleMonteCarlo2(
        thePayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the double-digital option is " << result << "\n";

    return 0;

}