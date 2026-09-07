#pragma once
#include "Node.h"
#include "Monitoring.h"
#include "MockNetwork.h"
#include "DataLoader.h"
#include "HashUtils.h"
#include <map>
#include <memory>
#include <vector>
#include <string>

class DistributionEngine {
public:
    DistributionEngine(int num_nodes, int virtual_nodes = 200);

    void routeAllRecords(const std::vector<Record>& records, bool verbose);
    //void routeRecord(const std::string& key, const std::string& value, bool verbose);
    void printStatistics();
    void persistAll(const std::string& folder);
    void collectMonitoring(Monitoring& monitor);
    Node* getNodeForKey(const std::string& key);

private:
    bool verbose;
    std::map<size_t, Node*> ring; // hash ring
    std::vector<std::unique_ptr<Node>> nodes;

    size_t hashKey(const std::string& key);
};
