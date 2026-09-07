#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct FieldSchema {
    std::string name;
    std::string type; // "string" or "int32"
};

class ConfigManager {
public:
    bool loadConfig(const std::string& filePath);
    const std::vector<FieldSchema>& getSchema() const;
    int getNumNodes() const;
    const std::vector<std::string>& getDataPaths() const;

private:
    std::vector<FieldSchema> schema;
    int numNodes = 0;
    std::vector<std::string> dataPaths;
};
