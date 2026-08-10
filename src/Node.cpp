#include "../include/Node.h"
#include <fstream>
#include <iostream>

using namespace std;

void Node::persist(const std::string& folder) {
    lock_guard<std::mutex> lock(mtx);
    string filename = "../" + folder + "/node" + std::to_string(node_id) + "_store.txt";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for persistence.\n";
        return;
    }
    for (const auto& kv : store) {
        file << kv.first << "," << kv.second << "\n";
    }
    file.close();
    cout << "Node " << node_id << " persisted " << store.size() << " records to " << filename << "\n";
}
