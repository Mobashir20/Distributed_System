#pragma once
#include <iostream>
#include <vector>

struct NodeStats {
    int node_id;
    std::size_t put_count = 0;
    std::size_t get_count = 0;
    std::size_t record_count = 0;
};

class Monitoring {
public:
    void addStats(const NodeStats& stats) {
        all_stats.push_back(stats);
    }

    void printSummary() {
        std::cout << "\n=== Monitoring Summary ===\n";
        for (const auto& s : all_stats) {
            std::cout << "Node " << s.node_id
                      << " | Records: " << s.record_count
                      << " | PUTs: " << s.put_count
                      << " | GETs: " << s.get_count
                      << "\n";
        }
        std::cout << "==========================\n";
    }

private:
    std::vector<NodeStats> all_stats;
};
