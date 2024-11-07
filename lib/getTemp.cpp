#include <iostream>
#include <fstream>
#include "getTemp.hpp"

using namespace std;

bool tryGetFileData(string &aFileData)
{
    string lFullPath = FILE_PATH + ID + "/" + FILE_NAME;
    
    bool lResult = false;
    
    ifstream lFileStream(lFullPath);    

    if (!lFileStream)
    {        
        cerr << "Error: Can't open file.\n";
        lResult = false;
    }
    else
    {    
        lResult = true;
        string lRow;
        while (getline(lFileStream, lRow)) // Read the rows.
            aFileData += lRow;  
    }

    lFileStream.close();
    
    return lResult;
}

bool tryGetTempFromData(string aFileData, double &aTempValue)
{
    bool lResult = true;
    aTempValue = 0;

    int lPos = aFileData.rfind("YES"); // Check if 'YES' exist.
    if (lPos == -1)
        return false;
    
    string lTempStr;

    lPos = aFileData.rfind("t=");
    if ( lPos != -1 )
    {
        lTempStr = aFileData.substr(lPos + 2, aFileData.length() - lPos - 2);
        aTempValue = stof(lTempStr) / 1000;
    }        
    else
        lResult = false;
    
    return lResult;
}
