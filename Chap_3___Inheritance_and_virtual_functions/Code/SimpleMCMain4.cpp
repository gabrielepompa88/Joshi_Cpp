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
    int optionTypeSelector;
    do
    {
        std::cout << "\nKind of option? (press 0 for 'calls', 1 for 'puts')\n";
        std::cin >> optionTypeSelector;
    } while ((optionTypeSelector != 0) & (optionTypeSelector != 1));

    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    PayOff* thePayOffPtr;

    switch (optionTypeSelector)
    {
    case 0:
        thePayOffPtr = new PayOffCall(Strike);
        break;
    case 1:
        thePayOffPtr = new PayOffPut(Strike);
        break;
    default:
        throw "Unknown option type found...";
    }

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double result{ SimpleMonteCarlo2(
        *thePayOffPtr,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };
    std::cout << "the price is " << result << "\n";

    delete thePayOffPtr;

    return 0;

}