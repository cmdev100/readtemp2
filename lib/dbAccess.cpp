#include <iostream>
#include "dbAccess.hpp"
#include <sqlite3.h>

const string qCreateTable = "CREATE TABLE IF NOT EXISTS TempData (ID INTEGER, TimeStamp INTEGER, Value REAL);";

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

bool tryCreateTable(sqlite3 **aConn);
bool tryOpenDb(sqlite3 **aConn);

bool tryStoreValue(int aId, int aTimestamp, double aTempValue)
{
    char *errMsg = 0;
    string qInsert = string("INSERT INTO TempData VALUES (") + to_string(aId) + "," + to_string(aTimestamp) + "," + to_string(aTempValue) + ")";

    sqlite3 *conn;
    
    if ( tryOpenDb(&conn) && tryCreateTable(&conn) )
    {
        int rc = sqlite3_exec(conn, qInsert.c_str(), callback, 0, &errMsg);
        
        if (rc != SQLITE_OK)
        {
            cerr << "Failed to execute query. Error: " + string(errMsg) << endl;
            return false;
        }
        
        sqlite3_close(conn);
    }
    else
    {
        sqlite3_close(conn);
        return false;
    }
    
    return true;
}

bool tryCreateTable(sqlite3 **aConn)
{
    char *errMsg = 0;
    
    int rc = sqlite3_exec(*aConn, qCreateTable.c_str(), callback, 0, &errMsg);

    if ( rc != SQLITE_OK )
    {
        cerr << "Failed to create table. Error: " << errMsg << endl;
        return false;
    }
    
    return true;
}

bool tryOpenDb(sqlite3 **aConn)
{
    int rc = sqlite3_open(dbPath.c_str(), &*aConn);
    if (rc)
    {
        cerr << "";
        return false;
    }  
    
    return true;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
