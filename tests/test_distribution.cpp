#include <gtest/gtest.h>
#include "../include/DistributionEngine.h"

TEST(DistributionEngineTest, EvenDistribution) {
    DistributionEngine engine(4, 100); // 4 nodes, 100 virtual nodes

    // Hash a bunch of keys
    int counts[4] = {0};
    for (int i = 0; i < 1000; ++i) {
        std::string key = "key" + std::to_string(i);
        Node* node = engine.getNodeForKey(key);
        counts[node->getId()]++;
    }

    // Check distribution is roughly even
    for (int i = 0; i < 4; ++i) {
        EXPECT_GT(counts[i], 200);   // each node gets at least ~20%
        EXPECT_LT(counts[i], 300);   // none gets more than ~30%
    }
}
