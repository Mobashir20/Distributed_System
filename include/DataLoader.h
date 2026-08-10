#pragma once
#include "ConfigManager.h"
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Record {
    vector<string> fields; // store parsed values as strings
};

class DataLoader {
public:
    explicit DataLoader(const ConfigManager& config);

    // Load all files specified in config.json
    void loadAllFiles();

    // Access loaded records
    const vector<Record>& getRecords() const;

private:
    const ConfigManager& config;
    vector<Record> records;
    unordered_set<string> seenKeys; // for duplicate detection

    Record parseLine(const string& line);
};
