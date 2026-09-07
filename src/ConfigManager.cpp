#include "../include/ConfigManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>    // Include exception for error handling
#include <stdexcept>    // Include exception for runtime_error
#include <nlohmann/json.hpp> // Include JSON library (https://github.com/nlohmann/json)

using json = nlohmann::json;

bool ConfigManager::loadConfig(const std::string& filePath) {
    try {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open config file " << filePath << std::endl;
            return false;
        }

        json j;
        try {
            file >> j;  // may throw if JSON is malformed
        } catch (const json::parse_error& e) {
            std::cerr << "JSON parse error in " << filePath
                      << ": " << e.what() << std::endl;
            return false;
        }

        // Parse schema safely
        if (!j.contains("schema") || !j["schema"].contains("fields")) {
            std::cerr << "Error: Missing 'schema.fields' in config file." << std::endl;
            return false;
        }

        for (const auto& field : j["schema"]["fields"]) {
            try {
                FieldSchema fs;
                fs.name = field.at("name").get<std::string>();
                fs.type = field.at("type").get<std::string>();
                schema.push_back(fs);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing schema field: " << e.what() << std::endl;
                return false;
            }
        }

        // Parse cluster info safely
        if (!j.contains("cluster") || !j["cluster"].contains("num_nodes")) {
            std::cerr << "Error: Missing 'cluster.num_nodes' in config file." << std::endl;
            return false;
        }

        try {
            numNodes = j["cluster"]["num_nodes"].get<int>();
            for (const auto& path : j["cluster"]["data_paths"]) {
                dataPaths.push_back(path.get<std::string>());
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing cluster info: " << e.what() << std::endl;
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error in loadConfig: " << e.what() << std::endl;
        return false;
    }
}


const std::vector<FieldSchema>& ConfigManager::getSchema() const {
    return schema;
}

int ConfigManager::getNumNodes() const {
    return numNodes;
}

const std::vector<std::string>& ConfigManager::getDataPaths() const {
    return dataPaths;
}
