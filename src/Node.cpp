#include "../include/Node.h"
#include <fstream>
#include <iostream>

void Node::persist(const std::string& folder) {
    std::lock_guard<std::mutex> lock(mtx);
    std::string filename = "../" + folder + "/node" + std::to_string(node_id) + "_store.txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for persistence.\n";
        return;
    }
    for (const auto& kv : store) {
        file << kv.first << "," << kv.second << "\n";
    }
    file.close();
    std::cout << "Node " << node_id << " persisted " << store.size()
              << " records to " << filename << "\n";
}
