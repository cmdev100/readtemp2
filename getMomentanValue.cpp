#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/getTemp.hpp"

using namespace std;

int main()
{
    string lFileData;
    if ( !tryGetFileData(lFileData) )
    {
        cerr << "Error: can't open the file.\n";
        return 1;     
    }

    double lTempValue;
    if ( !tryGetTempFromData(lFileData, lTempValue) )
    {
        cerr << "Error: can't get the temp data.\n";
        return 1;
    }

    stringstream lStream;

    lStream << fixed << setprecision(2) << lTempValue;

    cout << "Temp is: " + lStream.str() + " °C\n";

    return 0;
}