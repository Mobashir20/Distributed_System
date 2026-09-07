#include "../include/ConfigManager.h"
#include "../include/Verification.h"
#include <iostream>

int main() {
    bool verbose = false; // Set to true for detailed logging in Console
    /**************Config File Loading********************/
    // Opening Config File to read the schema and cluster info
    ConfigManager config;
    if (!config.loadConfig("../config.json")) {
        return 1;
    }

    std::cout << "Loaded Schema:\n";
    for (const auto& field : config.getSchema()) {
        std::cout << "  " << field.name << " : " << field.type << "\n";
    }

    std::cout << "\nCluster Info:\n";
    std::cout << "  Nodes: " << config.getNumNodes() << "\n";
    for (const auto& path : config.getDataPaths()) {
        std::cout << "  Data Path: " << path << "\n";
    }
   
    /***********DataLoader***********/
    // Step 1: Load Records
    DataLoader loader(config);
    loader.loadAllFiles();

    //Console Log to show the loaded records
    std::cout << "Loaded " << loader.getRecords().size() << " unique records.\n";
    if(verbose) {       //Console log to show the loaded records if verbose is true
        for (const auto& rec : loader.getRecords()) {
            for (const auto& field : rec.fields) {
                std::cout << field << " | ";
            }   
            std::cout << "\n";
        }
    }
    

    /********** Distribution Engine **********/
    // Step 2: Start Cluster and Route Records
    DistributionEngine engine(config.getNumNodes(),200); // 200 virtual nodes per physical node

    // Route records to nodes based on the first field (assumed to be a unique key)
    engine.routeAllRecords(loader.getRecords(), verbose);

    /********** Print Statistics **********/
    // Step 3: Print Statistics
    engine.printStatistics();

    /********** Persist Data **********/
    // Step 4: Persist all nodes to disk
    engine.persistAll("storage");

    /********** Monitoring **********/
    // Step 5: Collect monitoring stats and print summary
    Monitoring monitor;
    engine.collectMonitoring(monitor);
    monitor.printSummary();

    /********** Verification **********/
    // Step 6: Verify Record Distribution
    Verification::verifyRecords(engine, loader, verbose);

    return 0;
}

// Compilation :  
// g++ main.cpp -I  ../json-develop/include ConfigManager.cpp DataLoader.cpp DistributionEngine.cpp Node.cpp Verification.cpp MockNetwork.cpp -o Distributed_System

// Compilation from Distribution System command line :  
// g++ src/main.cpp -I include -I ../json-develop/include src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp src/HashUtils.cpp -o Distributed_System

// To run the application in Command line:  
// ./Distributed_System
