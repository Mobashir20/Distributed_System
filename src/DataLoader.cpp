#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

DataLoader::DataLoader(const ConfigManager& cfg) : config(cfg) {}

void DataLoader::loadAllFiles() {
    for (const auto& path : config.getDataPaths()) {
        // std::cout << "Loading file: " << path << std::endl;
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Warning: Cannot open file " << path << std::endl;
            continue;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Record rec = parseLine(line);

            // Use first field as unique key (e.g., "id")
            std::string key = rec.fields[0];
            // std::cout << "Key: " << key << std::endl;
            if (seenKeys.find(key) != seenKeys.end()) {
                continue; // skip duplicate
            }
            seenKeys.insert(key);

            records.push_back(rec);
        }
    }
}

Record DataLoader::parseLine(const std::string& line) {
    Record rec;
    std::stringstream ss(line);
    std::string token;
    size_t fieldIndex = 0;

    while (std::getline(ss, token, ',')) {
        // trim whitespace
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);

        // Validation: check schema type for this field
        if (fieldIndex < config.getSchema().size()) {
            //std::string type = config.getSchema()[fieldIndex].type;
            const auto& fieldSchema = config.getSchema()[fieldIndex];
            if (fieldSchema.type == "int32") {
                try {
                    (void)std::stoi(token); // just validate
                } catch (...) {
                    std::cerr << "Invalid int32 value at field index "
                              << fieldIndex << ": " << token << "\n";
                    token = "0"; // fallback or skip
                }
            }
        }

        rec.fields.push_back(token);
        fieldIndex++;
    }

    return rec;
}

/*Record DataLoader::parseLine(const std::string& line) {
    Record rec;
    std::stringstream ss(line);
    std::string token;
    size_t fieldIndex = 0;

    while (std::getline(ss, token, ',')) {
        // trim whitespace
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);

        FieldValue fv;
        fv.raw = token;

        // Look up schema type for this field
        if (fieldIndex < config.getSchema().size()) {
            fv.name = config.getSchema()[fieldIndex].name;
            fv.type = config.getSchema()[fieldIndex].type;

            if (fv.type == "int32") {
                try {
                    fv.intValue = std::stoi(token);
                } catch (...) {
                    std::cerr << "Invalid int32 value for field "
                              << fv.name << ": " << token << "\n";
                    fv.intValue = 0; // or skip/mark invalid
                }
            }
        }

        rec.fields.push_back(fv);
        fieldIndex++;
    }

    return rec;
}*/


const std::vector<Record>& DataLoader::getRecords() const {
    return records;
}
