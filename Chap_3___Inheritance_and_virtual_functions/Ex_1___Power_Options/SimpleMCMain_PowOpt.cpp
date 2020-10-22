// SimpleMCMain_PowOpt.cpp
//
// main for call/put power options.

#include "SimpleMC2.h"
#include "PowerOptions.h"
#include <iostream>

int main()
{
    double Expiry;
    double Strike;
    int Power;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;

    //read in parameters
    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;

    std::cout << "\nEnter Strike\n";
    std::cin >> Strike;

    std::cout << "\nEnter Power\n";
    std::cin >> Power;

    const PayOffCallPowerOption callPowOptPayOff(Strike, Power);
    const PayOffPutPowerOption putPowOptPayOff(Strike, Power);

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter vol\n";
    std::cin >> Vol;

    std::cout << "\nEnter r\n";
    std::cin >> r;

    std::cout << "\n Number of paths\n";
    std::cin >> NumberOfPath;

    double resultCall{ SimpleMonteCarlo2(
        callPowOptPayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    double resultPut{ SimpleMonteCarlo2(
        putPowOptPayOff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath) };

    std::cout << "the price of the call power option is " << resultCall << "\n";
    std::cout << "the price of the put power option is " << resultPut << "\n";

    return 0;

}