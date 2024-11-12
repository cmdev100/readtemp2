#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/dbAccess.hpp"

using namespace std;

int main()
{
    list<StoredValue> lValueList;
    char aBuffer[21];
    int lCount = 5;

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