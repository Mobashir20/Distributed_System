#include "../include/DistributionEngine.h"
#include <functional>
#include <iostream>

DistributionEngine::DistributionEngine(int num_nodes, int virtual_nodes) {
    for (int i = 0; i < num_nodes; ++i) {
        nodes.push_back(std::make_unique<Node>(i));
        for (int v = 0; v < virtual_nodes; ++v) {
            //std::hash<std::string> hasher;
            std::size_t h = HashUtils::fnv1aHash("NODE_" + std::to_string(i) + "_VNODE_" + std::to_string(v) + "_SEED_" + std::to_string(rand()));
            ring[h] = nodes[i].get();
        }
    }
}

std::size_t DistributionEngine::hashKey(const std::string& key) {
    //std::hash<std::string> hasher;
    return HashUtils::fnv1aHash(key);
}

Node* DistributionEngine::getNodeForKey(const std::string& key) {
    std::size_t h = hashKey(key);
    auto it = ring.lower_bound(h);
    if (it == ring.end()) {
        return ring.begin()->second;
    }
    return it->second;
}

void DistributionEngine::routeAllRecords(const std::vector<Record>& records, bool verbose) {
    std::unordered_map<int, std::vector<std::string>> batches;

    // Group records by destination node
    for (const auto& rec : records) {
        std::string key = rec.fields[0];
        std::string value;
        for (size_t i = 1; i < rec.fields.size(); ++i) {
            value += rec.fields[i] + " ";
        }
        Node* node = getNodeForKey(key);
        batches[node->getId()].push_back(key + ":" + value);
    }

    // Send one batch per node
    for (auto& [nodeId, payloads] : batches) {
        MockSocket sock(999, verbose);  // verbose flag controls logging
        sock.connect(nodeId);

        // Concatenate all records into one payload
        std::string batch;
        for (const auto& p : payloads) batch += p + "\n";

        sock.send(batch);

        std::cout << "Sent " << payloads.size()
                      << " records in one batch to Node " << nodeId << "\n";

        // Deliver to node
        for (const auto& p : payloads) {
            auto pos = p.find(":");
            std::string key = p.substr(0, pos);
            std::string value = p.substr(pos + 1);
            nodes[nodeId]->put(key, value);
        }
    }
}


/*void DistributionEngine::routeRecord(const std::string& key, const std::string& value, bool verbose) {
    Node* node = getNodeForKey(key);
    // Simulate network transfer
    MockSocket sock(999, verbose); // mock client socket
    sock.connect(node->getId());
    sock.send(key + ":" + value);
    std::string received = sock.recv();
    node->put(key, value);
}*/

void DistributionEngine::printStatistics() {
    long long totalRecords = 0;
    for (auto& node : nodes) {
        std::cout << "Node " << node->getId()
                  << " has " << node->getRecordCount()
                  << " unique records.\n";
        totalRecords += static_cast<long long>(node->getRecordCount());
    }
    std::cout << "Total Unique records: " << totalRecords << "\n";
}

// persist all nodes
void DistributionEngine::persistAll(const std::string& folder) {
    for (auto& node : nodes) {
        node->persist(folder);
    }
}

// collect monitoring stats
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
