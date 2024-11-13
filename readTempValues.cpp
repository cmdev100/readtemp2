#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/dbAccess.hpp"

using namespace std;

int main(int argc, char *argv[])
{   
    list<StoredValue> lValueList;
    char aBuffer[21];
    const int DEFAULT_COUNT = 5;
    int lCount;    
    string lErrMsg = "Wrong or no count param, using 5.";
    
    if ( argc == 2 )
    {
        try {
            lCount = stoi(argv[1]);
        }    
        catch (...) {
            cout << lErrMsg << endl;
            lCount = DEFAULT_COUNT;
        }
    }    
    else
    {
        lCount = DEFAULT_COUNT;
        cout << lErrMsg << endl;
    }   
        
    getValues(lValueList, lCount);      

    for ( StoredValue lVal : lValueList )
    {
        // The value
        stringstream lStream;
        lStream << fixed << setprecision(2) << lVal.Value;

        // Time timestamp
        strftime(aBuffer, sizeof(aBuffer), "%F %T", localtime(&lVal.Timestamp));

        string lOutStr = "( " + to_string(lVal.Id) + " | "s + aBuffer + " | "s + lStream.str() + " )";
        cout << lOutStr << endl;
    }    

    return 0;
}