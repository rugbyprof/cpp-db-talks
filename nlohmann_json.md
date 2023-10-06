## Json

`nlohmann/json` is a widely-used header-only library for C++ that provides a convenient way to handle JSON data. Authored by Niels Lohmann, the library makes it very easy to convert between JSON text and C++ objects.

### Main Features:
1. **Intuitive Syntax**: With `nlohmann/json`, you can use modern C++ constructs, like initializer lists or range-based for loops, making the JSON interactions feel very natural.

2. **Header-only**: Just include the header and you're set. No need to link against additional libraries, making it convenient for integration.

3. **STL-like access**: The library provides array and object types that mimic the STL containers.

4. **Implicit conversions**: Converts between JSON values and C++ types automatically.

5. **Serialization and Deserialization**: Provides functionality to serialize C++ objects to JSON and vice versa.

### Basic Usage:

1. **Including the Library**:
   ```cpp
   #include <nlohmann/json.hpp>
   using json = nlohmann::json;
   ```

2. **Parsing JSON**:
   ```cpp
   std::string jsonString = R"({"name": "John", "age": 30, "city": "New York"})";
   json jsonObj = json::parse(jsonString);
   ```

3. **Accessing and Modifying Values**:
   ```cpp
   std::string name = jsonObj["name"];  // Access value
   jsonObj["age"] = 31;                 // Modify value
   ```

4. **Iterating**:
   ```cpp
   for (json::iterator it = jsonObj.begin(); it != jsonObj.end(); ++it) {
       std::cout << it.key() << " : " << it.value() << "\n";
   }
   ```

5. **Creating JSON**:
   ```cpp
   json j = {
       {"name", "John"},
       {"age", 30},
       {"is_student", false},
       {"hobbies", {"reading", "gaming", "coding"}}
   };
   ```

6. **Serialization and Deserialization**:
   If you have custom classes, you can define how to convert them to/from JSON by providing `to_json` and `from_json` methods.

### Integration:

Since it's a header-only library, you only need to include the JSON header file in your project. You can obtain the library via various package managers, by downloading it directly from its GitHub repository, or by using it as a submodule if you're using Git for version control.

### Note:

The library requires a C++11 compatible compiler, so ensure you have set the appropriate compilation flags (`-std=c++11` or similar, depending on your compiler).

