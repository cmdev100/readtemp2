#include <iostream>
#include "dbAccess.hpp"
#include <sqlite3.h>
#include <string.h>

const string qCreateTable = "CREATE TABLE IF NOT EXISTS TempData (ID INTEGER, TimeStamp INTEGER, Value REAL);";

bool tryCreateTable(sqlite3 **aConn);
bool tryOpenDb(sqlite3 **aConn);

bool tryStoreValue(int aId, int aTimestamp, double aTempValue)
{
    char *errMsg = 0;
    string qInsert = string("INSERT INTO TempData VALUES (") + to_string(aId) + "," + to_string(aTimestamp) + "," + to_string(aTempValue) + ")";

    sqlite3 *conn;
    
    if ( tryOpenDb(&conn) && tryCreateTable(&conn) )
    {
        int rc = sqlite3_exec(conn, qInsert.c_str(), NULL, 0, &errMsg);
        
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

void getValues(list<StoredValue> &aList, int aCount)
{
    sqlite3 *conn;
    sqlite3_stmt* stmt;

    string qSql = "SELECT * FROM 'TempData' ORDER BY Timestamp DESC LIMIT " + to_string(aCount);

    if ( tryOpenDb(&conn) )
    {
        int rc = sqlite3_prepare_v2(conn, qSql.c_str(), -1, &stmt, NULL);

        if( rc != SQLITE_OK )
        {
            cerr << "Error: failed to open query. Reason: "s + sqlite3_errmsg(conn) << endl;
            sqlite3_free(stmt);
            return;
        }
        
        int NoOfCols = sqlite3_column_count(stmt);

        bool done = false;

        const char* COL_ID = "ID";
        const char* COL_TIMESTAMP = "TimeStamp";
        const char* COL_VALUE = "Value";

        struct StoredValue lSV;
        
        while(!done)
        { 
            switch(sqlite3_step(stmt))
            {
                case SQLITE_ROW: 
                    lSV.Id = - 1;
                    lSV.Timestamp = 0;
                    lSV.Value = -1;

                    for ( int i = 0; i < NoOfCols; i++ )
                    {
                        const char* colName =  sqlite3_column_name(stmt, i); 
                        
                        if ( strcmp(COL_ID, colName) == 0 )
                            lSV.Id = sqlite3_column_int(stmt, i);
                        else if ( strcmp(COL_TIMESTAMP, colName) == 0 )
                            lSV.Timestamp = sqlite3_column_int(stmt, i);
                        else if ( strcmp(COL_VALUE, colName) == 0 )
                            lSV.Value = sqlite3_column_double(stmt, i);
                        else
                            continue;                                                 
                    }                    
                    if ( lSV.Id != -1 )
                        aList.push_back(lSV);                
                    break;
                case SQLITE_DONE:
                    sqlite3_finalize(stmt);
                    done = true;
                    break;
            }
        }
    }
    
    // Sort list by timestamp.
    aList.sort();

    sqlite3_close(conn);   
}

bool tryCreateTable(sqlite3 **aConn)
{
    char *errMsg = 0;
    
    int rc = sqlite3_exec(*aConn, qCreateTable.c_str(), NULL, NULL, &errMsg);

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
