#include "..\include\ConfigManager.h"
#include "..\include\Verification.h"
#include <iostream>

using namespace std;

int main() {
    /**************Config File Loading********************/
    //Opening Config File to read the schema and cluster info
    ConfigManager config;
    if (!config.loadConfig("config.json")) {
        return 1;
    }

    cout << "Loaded Schema:\n";
    for (const auto& field : config.getSchema()) {
        cout << "  " << field.name << " : " << field.type << "\n";
    }

    cout << "\nCluster Info:\n";
    cout << "  Nodes: " << config.getNumNodes() << "\n";
    for (const auto& path : config.getDataPaths()) {
        cout << "  Data Path: " << path << "\n";
    }
   
    /***********DataLoader***********/
    //Step 1: Load Records

    DataLoader loader(config);
    loader.loadAllFiles();

    cout << "Loaded " << loader.getRecords().size() << " unique records.\n";

    for (const auto& rec : loader.getRecords()) {
        for (const auto& field : rec.fields) {
            cout << field << " | ";
        }
        cout << "\n";
    }

    /********** Distribution Engine **********/
    //Step 2: Start Cluster and Route Records
    DistributionEngine engine(config.getNumNodes());

     //Route records to nodes based on the first field (assumed to be a unique key)
    for (const auto& rec : loader.getRecords()) {
        string key = rec.fields[0]; // assume first field is unique key
        string value;
        for (size_t i = 1; i < rec.fields.size(); ++i) {
            value += rec.fields[i] + " ";
        }
        engine.routeRecord(key, value);
    }

    /********** Print Statistics **********/
    //Step 3: Print Statistics
    engine.printStatistics();

    /********** Persist Data **********/
    //Step 4:Persist all nodes to disk
    engine.persistAll("storage");


    /********** Monitoring **********/
    //Step 5 : Collect monitoring stats and print summary
    Monitoring monitor;

    // Collect monitoring stats and print summary
    engine.collectMonitoring(monitor);
    monitor.printSummary();

    /********** Verification **********/
    //Step 6: Verify Record Distribution
    Verification::verifyRecords(engine, loader);

    return 0;
}

//Compilation :  g++ main.cpp -I  ../json-develop/include ConfigManager.cpp DataLoader.cpp DistributionEngine.cpp Node.cpp Verification.cpp MockNetwork.cpp -o Distributed_System

//Compilation from Distribution System command line : g++ src/main.cpp -I include -I ../json-develop/include src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp -o Distributed_System

//To run the application in Command line:  .\Distributed_System
