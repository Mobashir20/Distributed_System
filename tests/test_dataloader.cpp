#include <gtest/gtest.h>
#include "../include/DataLoader.h"
#include "../include/ConfigManager.h"

TEST(DataLoaderTest, SalaryValidation) {
    ConfigManager cfg;
    if (!cfg.loadConfig("config.json")) {
        return ;
    }

    DataLoader loader(cfg);

    Record rec = loader.parseLine("1,Name1,30001");
    EXPECT_EQ(rec.fields[2], "30001"); // salary parsed correctly

    Record badRec = loader.parseLine("2,Name2,NotANumber");
    EXPECT_EQ(badRec.fields[2], "0");  // fallback applied
}


//g++ -std=c++17 -Iinclude -I../json-develop/include -Isrc -Itests/gtest tests/test_dataloader.cpp tests/test_distribution.cpp src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp src/HashUtils.cpp tests/libgtest.a tests/libgtest_main.a -lpthread -o runTests

//g++ -std=c++17 -Iinclude -I../json-develop/include -Isrc -Itests tests/test_dataloader.cpp src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp src/HashUtils.cpp tests/libgtest.a tests/libgtest_main.a -lpthread -o runTests
