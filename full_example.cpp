/**
 * g++ full_example.cpp -std=c++17 -o full_example.exe
*/

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <sqlite3.h>
#include <string>

// Alias for convenience
using json = nlohmann::json;
using namespace std;


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
  }
  std::cout << "\n";
  return 0;
}


// Function to read a JSON file and return a json object
json readJSONFile(const std::string &filename) {
    std::ifstream inputFile(filename);
    
    // Check if file opening was successful
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    json jsonData;
    inputFile >> jsonData;

    return jsonData;
}

// int main(int argc, char** argv) {
//     try {
//         const std::string filename = argv[1];  // Replace with your file path
//         json data = readJSONFile(filename);
//         std::cout << "Read JSON data:\n" << data.dump(4) << std::endl;
//     } catch (const std::exception &e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
//     return 0;
// }

class SLH{
    int conn;
    sqlite3 *db;
    int conn;
    SLH(char* dbname){
        conn = sqlite3_open(dbname, &db);
    }
    void setDBName(char* dbname){
        conn = sqlite3_open(dbname, &db);
    }

    bool createTable(string queryTxt){

    }
};

int main(int argc, char** argv) {
  sqlite3 *db;
  char *errMsg = 0;
  int conn;
  string dbname;

  // Open database
  conn = sqlite3_open("test.db", &db);
  if (conn) {
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
  conn = sqlite3_exec(db, sql, callback, 0, &errMsg);
  if (conn != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Insert data
  sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
        "VALUES (1, 'Paul', 32, 'California', 20000.00 );";
  conn = sqlite3_exec(db, sql, callback, 0, &errMsg);
  // ... Insert more data as needed

  // Fetch data
  sql = "SELECT * from COMPANY;";
  conn = sqlite3_exec(db, sql, callback, 0, &errMsg);

  // Close database
  sqlite3_close(db);
  return 0;
}