#ifndef DB_ACCESS
#define DB_ACCESS
#include <list>

using namespace std;

const string dbPath = "readtemp.db";

struct StoredValue {
  int Id;
  time_t Timestamp;
  double Value;
  bool operator < (const StoredValue& cmp)
  {
    return Timestamp < cmp.Timestamp;
  }
};

bool tryStoreValue(int aId, int aTimestamp, double aTempValue);
void getValues(list<StoredValue> &aList, int aCount);

#endif