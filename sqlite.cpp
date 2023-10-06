/**
 * This file is an example on 
 *   - how to connect to sqlite
 *   - create a table
 *   - insert a row of data
 *   - select and display said data
*/

#include <iostream>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
  }
  std::cout << "\n";
  return 0;
}

int main() {
  sqlite3 *db;
  char *errMsg = 0;
  int rc;

  // Open database
  rc = sqlite3_open("test.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 0;
  }

  // Create table
  const char *sql = "CREATE TABLE COMPANY("
                    "ID INT PRIMARY KEY NOT NULL,"
                    "NAME TEXT NOT NULL,"
                    "AGE INT NOT NULL,"
                    "ADDRESS CHAR(50),"
                    "SALARY REAL );";
  rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Insert data
  sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
        "VALUES (1, 'Paul', 32, 'California', 20000.00 );";
  rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
  // ... Insert more data as needed

  // Fetch data
  sql = "SELECT * from COMPANY;";
  rc = sqlite3_exec(db, sql, callback, 0, &errMsg);

  // Close database
  sqlite3_close(db);
  return 0;
}