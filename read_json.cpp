#include <iostream>
#include <fstream>
#include "json.hpp"

// Alias for convenience
using json = nlohmann::json;

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

int main(int argc, char** argv) {
    try {
        const std::string filename = argv[1];  // Replace with your file path
        json data = readJSONFile(filename);
        std::cout << "Read JSON data:\n" << data.dump(4) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
