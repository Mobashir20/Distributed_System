#include "..\include\ConfigManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp> // Include JSON library (https://github.com/nlohmann/json)

using json = nlohmann::json;
using namespace std;

bool ConfigManager::loadConfig(const std::string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Cannot open config file " << filePath << std::endl;
        return false;
    }

    json j;
    file >> j;

    // Parse schema
    for (const auto& field : j["schema"]["fields"]) {
        FieldSchema fs;
        fs.name = field["name"];
        fs.type = field["type"];
        schema.push_back(fs);
    }

    // Parse cluster info
    numNodes = j["cluster"]["num_nodes"];
    for (const auto& path : j["cluster"]["data_paths"]) {
        dataPaths.push_back(path);
    }

    return true;
}

const vector<FieldSchema>& ConfigManager::getSchema() const {
    return schema;
}

int ConfigManager::getNumNodes() const {
    return numNodes;
}

const vector<string>& ConfigManager::getDataPaths() const {
    return dataPaths;
}

