#pragma once
#include "ConfigManager.h"
#include <string>
#include <vector>
#include <unordered_set>


struct Record {
    //std::vector<FieldValue> fields;
    std::vector<std::string> fields; // store parsed values as strings
};

class DataLoader {
public:
    explicit DataLoader(const ConfigManager& config);

    // Load all files specified in config.json
    void loadAllFiles();
    Record parseLine(const std::string& line);

    // Access loaded records
    const std::vector<Record>& getRecords() const;

private:
    const ConfigManager& config;
    std::vector<Record> records;
    std::unordered_set<std::string> seenKeys; // for duplicate detection

    
};
