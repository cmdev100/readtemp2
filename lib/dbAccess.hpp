#ifndef DB_ACCESS
#define DB_ACCESS

using namespace std;

const string dbPath = "readtemp.db";

bool tryStoreValue(int aId, int aTimestamp, double aTempValue);

#endif