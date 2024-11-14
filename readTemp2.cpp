#include <iostream>
#include <unistd.h>
#include <ctime>
#include "lib/dbAccess.hpp"
#include "lib/getTemp.hpp"
using namespace std;

int main ()
{
    bool lSampled = false;
    char aBuffer[21];  // the size of 'YYYY-MM-DD HH:NN:SS'
    time_t lSampleTimestamp, lTimestamp;
    double lTempValue;

    while (true)
    {      
        lTimestamp = time(0); // Get the current time.

        struct tm date = *localtime(&lTimestamp); // Convert to a tm structure.

        if ( date.tm_min == 0 ) // For hourly timestamps.
        {
            if ( !lSampled )
            {
                date.tm_sec = 0;
                lSampleTimestamp  = mktime(&date);
                lTempValue = 0;
                
                if ( !tryGetTemp(lTempValue) || !tryStoreValue(1, lSampleTimestamp, lTempValue) )
                {
                    strftime(aBuffer, sizeof(aBuffer), "%F %T", &date);
                    cout << "Failed to sample value for " << aBuffer << endl;
                }       
                lSampled = true;
            }
        }
        else
            lSampled = false;
      
        sleep(5);
    }
    return 0;
}