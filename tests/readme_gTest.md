## Compiler Details:
We are using G++ compiler from MSYS2 (https://www.msys2.org/)
Text Editor used : VS Code


## To Build/Compile use below:
Run in Distributed_System Directory : g++ -std=c++17 -Iinclude -I../json-develop/include -Isrc -Itests tests/test_dataloader.cpp src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp src/HashUtils.cpp tests/libgtest.a tests/libgtest_main.a -lpthread -o runTests

##To run gTest.
Run in Distributed_System Directory : run ./runTests.exe