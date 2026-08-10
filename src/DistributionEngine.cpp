#include "../include/DistributionEngine.h"
#include <functional>
#include <iostream>

using namespace std;

DistributionEngine::DistributionEngine(int num_nodes, int virtual_nodes) {
    for (int i = 0; i < num_nodes; ++i) {
        nodes.push_back(std::make_unique<Node>(i));
        for (int v = 0; v < virtual_nodes; ++v) {
            hash<string> hasher;
            size_t h = hasher("NODE_" + std::to_string(i) + "_VNODE_" + std::to_string(v));
            ring[h] = nodes[i].get();
        }
    }
}

size_t DistributionEngine::hashKey(const std::string& key) {
    std::hash<std::string> hasher;
    return hasher(key);
}

Node* DistributionEngine::getNodeForKey(const std::string& key) {
    size_t h = hashKey(key);
    auto it = ring.lower_bound(h);
    if (it == ring.end()) {
        return ring.begin()->second;
    }
    return it->second;
}

void DistributionEngine::routeRecord(const std::string& key, const std::string& value) {
    Node* node = getNodeForKey(key);
    // Simulate network transfer
    MockSocket sock(999); // mock client socket
    sock.connect(node->getId());
    sock.send(key + ":" + value);
    std::string received = sock.recv();
    node->put(key, value);
}

void DistributionEngine::printStatistics() {
    long long totalRecords = 0;
    for (auto& node : nodes) {
        cout << "Node " << node->getId()
                << " has " << node->getRecordCount()
                << " unique records.\n";
        totalRecords += static_cast<long long>(node->getRecordCount());
    }
    cout << "Total Unique records: " << totalRecords << "\n";
}

// persist all nodes
void DistributionEngine::persistAll(const std::string& folder) {
    for (auto& node : nodes) {
        node->persist(folder);
    }
}

//collect monitoring stats
void DistributionEngine::collectMonitoring(Monitoring& monitor) {
    for (auto& node : nodes) {
        NodeStats stats;
        stats.node_id = node->getId();
        stats.record_count = node->getRecordCount();
        stats.put_count = node->getPutCount();
        stats.get_count = node->getGetCount();
        monitor.addStats(stats);
    }
}

