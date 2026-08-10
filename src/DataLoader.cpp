#include "..\include\DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

DataLoader::DataLoader(const ConfigManager& cfg) : config(cfg) {}

void DataLoader::loadAllFiles() {
    for (const auto& path : config.getDataPaths()) {
        //cout << "Loading file: " << path << endl;
        ifstream file(path);
        if (!file.is_open()) {
            cerr << "Warning: Cannot open file " << path << endl;
            continue;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            Record rec = parseLine(line);

            // Use first field as unique key (e.g., "id")
            string key = rec.fields[0];
            //cout<<"Key: "<<key<<endl;
            if (seenKeys.find(key) != seenKeys.end()) {
                continue; // skip duplicate
            }
            seenKeys.insert(key);

            records.push_back(rec);
        }
    }
}

Record DataLoader::parseLine(const string& line) {
    Record rec;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        // trim whitespace
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        rec.fields.push_back(token);
    }

    return rec;
}

const vector<Record>& DataLoader::getRecords() const {
    return records;
}
