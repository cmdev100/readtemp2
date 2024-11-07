#ifndef GET_TEMP
#define GET_TEMP

using namespace std;

const string FILE_PATH = "/sys/bus/w1/devices/";
const string FILE_NAME = "w1_slave";
const string ID = "28-80000026bb60";

bool tryGetFileData(string &aFileData);
bool tryGetTempFromData(string aFileData, double &aTempValue);

#endif
