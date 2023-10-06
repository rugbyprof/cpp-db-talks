## Sqlite

### Getting started with SQLite and C++:

1. **Setup**:
   You'll first need to make sure SQLite is installed. SQLite comes pre-installed with many OS distributions. If it's not installed, you can get it from the official [SQLite website](https://www.sqlite.org/).

2. **Code Example**:

Here's a basic CRUD example using SQLite with C++:

```cpp
#include <iostream>
#include <sqlite3.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "\n";
    return 0;
}

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }

    // Create table
    const char* sql = "CREATE TABLE COMPANY(" \
                      "ID INT PRIMARY KEY NOT NULL," \
                      "NAME TEXT NOT NULL," \
                      "AGE INT NOT NULL," \
                      "ADDRESS CHAR(50)," \
                      "SALARY REAL );";
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Insert data
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
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
```

### Compiling and Running:

You need to link against the SQLite library when compiling:

```bash
g++ your_file_name.cpp -lsqlite3 -o output_name
```

Of course, Terry! Let's dive into the `sqlite3_exec()` function and its callback mechanism.

---

## sqlite3_exec() Overview:

The `sqlite3_exec()` function is a convenience function provided by the SQLite C API that allows users to execute SQL statements without having to manually prepare, step through, and finalize SQL statement objects. 

Its signature is:
```c
int sqlite3_exec(
  sqlite3* db,           /* The database on which the SQL executes */
  const char *sql,       /* The SQL to be executed */
  int (*callback)(void*,int,char**,char**), /* Callback function */
  void *arg,             /* 1st argument to callback */
  char **errmsg          /* Error msg written here */
);
```

## Callback Function:

The `callback` function is an optional parameter. If it's not NULL, SQLite will call it for each row of result that the SQL statement produces. This is useful when the SQL statement is a `SELECT` or when it's a statement (like `INSERT` or `UPDATE`) that returns data.

The callback function has the following signature:
```c
int callback(void *arg, int num_columns, char **column_values, char **column_names);
```

1. `void *arg`: This is the same pointer passed as the 4th argument to `sqlite3_exec()`. It's a way for you to pass data into the callback.

2. `int num_columns`: The number of columns in the result.

3. `char **column_values`: An array of strings representing the data for the row. Each string is a single field of the result.

4. `char **column_names`: An array of strings representing the names of the columns. The first string will be the name of the first column, and so on.

### Example:

Here's a simple example to illustrate:

```c
#include <sqlite3.h>
#include <stdio.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;

    // Open database
    sqlite3_open("test.db", &db);

    // Execute SQL statement with a callback
    const char *sql = "SELECT * FROM some_table";
    sqlite3_exec(db, sql, callback, 0, &errMsg);

    // Close database
    sqlite3_close(db);
}
```

In this example, the `callback` function simply prints out the column name and its value for each row of the result set.

### Important Notes:

- If the callback returns a non-zero value, the `sqlite3_exec()` function will return `SQLITE_ABORT` and halt any further processing of the SQL.
- If `errmsg` is not NULL, and an error occurs while executing the SQL, then an error message will be written to `errmsg`.
- You should handle and free the error message using `sqlite3_free()` to prevent memory leaks.

### Conclusion:

The `callback` mechanism in `sqlite3_exec()` provides a handy way to process query results row-by-row without the need for more verbose SQLite C API functions. However, for more complex operations or when dealing with binary data, you might consider using the manual step-by-step approach with `sqlite3_prepare_v2()`, `sqlite3_step()`, and `sqlite3_finalize()`.