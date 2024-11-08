#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/getTemp.hpp"

using namespace std;

int main()
{
    
    double lTempValue;

    if ( !tryGetTemp(lTempValue) )
    {
        cout << "Couldn't get the temp value.\n";
        return 1;
    }
    else
    {
        stringstream lStream;

        lStream << fixed << setprecision(2) << lTempValue;

        cout << "Temperature is: " + lStream.str() + " °C\n";
    } 
    return 0;
}