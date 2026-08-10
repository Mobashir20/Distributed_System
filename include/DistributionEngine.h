#include "Node.h"
#include "Monitoring.h"
#include "MockNetwork.h"
#include <map>
#include <memory>
#include <vector>
#include <string>

class DistributionEngine {
public:
    DistributionEngine(int num_nodes, int virtual_nodes = 10);

    void routeRecord(const std::string& key, const std::string& value);
    void printStatistics();
    void persistAll(const std::string& folder);
    void collectMonitoring(Monitoring& monitor);
    Node* getNodeForKey(const std::string& key);

private:
    std::map<size_t, Node*> ring; // hash ring
    std::vector<std::unique_ptr<Node>> nodes;

    size_t hashKey(const std::string& key);
};
