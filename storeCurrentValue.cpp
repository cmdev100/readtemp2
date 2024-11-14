#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "lib/dbAccess.hpp"
#include "lib/getTemp.hpp"

using namespace std;

int main()
{
    double lTempValue;

    if ( !tryGetTemp(lTempValue) )
    {
        cerr << "Can't get any temp value.\n";
        return 1;
    }
    else
    {
        // Id for the sensor. (primary key)
        int lId = 1;
                l
        // Get current timestamp.
        time_t timestamp = time(0); 
        
        if ( tryStoreValue(lId, timestamp, lTempValue) )
        {     
            stringstream lStream;
            lStream << fixed << setprecision(2) << lTempValue;
            char aBuffer[21];
            strftime(aBuffer, sizeof(aBuffer), "%F %T", localtime(&timestamp));
            cout << "Current value (" + lStream.str() + " °C) stored at " + aBuffer + ".\n";
        }            
        else
        {
            cerr << "Failed to store value.\n";
            return 1;
        }            
    }
                
    return 0;
}