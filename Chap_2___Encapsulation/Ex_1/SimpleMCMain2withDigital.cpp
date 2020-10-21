// SimpleMCMain2.cpp
//
// Ex.1 : Digitals included

#include "PayOff1.h" // explicitly included here otherwise the wrong one gets included from SimpleMC.h
#include "SimpleMC.h"
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
        std::cout << "\nKind of option? (press 0 for 'calls', 1 for 'puts', 2 for 'digital-calls', 3 for 'digital-puts')\n";
        std::cin >> optionTypeSelector;
    } while ((optionTypeSelector != 0) & (optionTypeSelector != 1) & (optionTypeSelector != 2) & (optionTypeSelector != 3));

    PayOff::OptionType theOptionsType;

    switch (optionTypeSelector)
    {
    case 0:
        theOptionsType = PayOff::OptionType::call;
        break;
    case 1:
        theOptionsType = PayOff::OptionType::put;
        break;
    case 2:
        theOptionsType = PayOff::OptionType::callDigital;
        break;
    case 3:
        theOptionsType = PayOff::OptionType::putDigital;
        break;
    default:
        throw "Unknown option type found...";
    }

    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    PayOff thisPayOff(Strike, theOptionsType);

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double result{ SimpleMonteCarlo2(
        thisPayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };
    std::cout << "the price is " << result << "\n";

    return 0;

}