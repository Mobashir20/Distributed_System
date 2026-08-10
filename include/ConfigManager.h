#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct FieldSchema {
    string name;
    string type; // "string" or "int32"
};

class ConfigManager {
public:
    bool loadConfig(const string& filePath);
    const vector<FieldSchema>& getSchema() const;
    int getNumNodes() const;
    const vector<string>& getDataPaths() const;

private:
    vector<FieldSchema> schema;
    int numNodes = 0;
    vector<string> dataPaths;
};
