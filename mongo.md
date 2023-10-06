## MongoDB

Using MongoDB with C++ involves a bit more setup than Sqlite, but it's a powerful tool to have in your belt, especially for more complex data structures or when you scale up. 

Here's how you can get started:

### Setting up MongoDB and the C++ Driver:

1. **Install MongoDB**:
   - Follow the instructions on the [official MongoDB website](https://docs.mongodb.com/manual/installation/) to install MongoDB.

2. **Install the MongoDB C++ Driver**:
   - MongoDB provides a C++ driver called `mongocxx`. You'll need to install both the C driver (`libmongoc`) and the C++ driver (`libmongocxx`).
   - Detailed instructions can be found in the [official documentation](http://mongocxx.org/mongocxx-v3/installation/).

### Code Example:

Here's a basic CRUD example using `mongocxx`:

```cpp
#include <iostream>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

int main() {
    // Connect to the database
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    // Access the database and the collection
    auto db = conn["testdb"];
    auto collection = db["testcollection"];

    // Insert a document
    bsoncxx::document::value new_document = bsoncxx::builder::stream::document{} 
        << "name" << "John" 
        << "age" << 25 
        << bsoncxx::builder::stream::finalize;
    collection.insert_one(new_document.view());

    // Fetch data
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }

    // Additional CRUD operations can be implemented similarly.

    return 0;
}
```

### Compiling and Running:
   
You need to include the path to the MongoDB C++ driver headers and link against the required libraries:

```bash
g++ your_file_name.cpp -Ipath_to_mongocxx_include -Lpath_to_mongocxx_lib -lmongocxx -lbsoncxx -o output_name
```

Replace `path_to_mongocxx_include` and `path_to_mongocxx_lib` with the paths where you installed the MongoDB C++ driver.

### Conclusion:

- MongoDB is schema-less, which makes it more flexible in terms of data structures.
- While SQLite is a relational database, MongoDB is a NoSQL database. The data model between the two is different, and MongoDB stores data in a JSON-like format (BSON).
- The setup for MongoDB is a bit more complex than SQLite, especially for beginners.

