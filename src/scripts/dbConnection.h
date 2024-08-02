#define dbConnection_H_

typedef struct sqlite3 sqlite3;



int sqlite3_open(
    const char *bengalaDB, 
    sqlite3 **ppDB
);


int sqlite3_close();

