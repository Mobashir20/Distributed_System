### High Level Architecture:
1. Config Manager
    a. Load : config.json
    b. Defines schema (fields, types: string, int)
    c. Define cluster size and data file paths.

2. Data Loader
    a. Reads local data files line by line (<= 100 MB).
    b. Parses records accprding tp schems.
    c. Remove duplicates.
    d. Prepares records for distribution.

3. Cluster Manager / Distribution Engine
    a. Implements consistent hashing to decide which node owns each record.
    b. Provides routeRecord(key, value) to transfer records to the correct node.
    c. Uses MockSocket(connect/send/ recv) to simulate network I/O between nodes.

4. Node
    a. Represents a single partition.
    b. Stores records in memory.
    c. Provides put() and get() operations.
    d. Tracks statistics (record count, put/get counts).
    e. Persists data to disk (storage/nodeX_store.txt).

5. NodeServer (Mock Server - MockServer)
    a. Simulates independent node processes.
    b. Runs a server loop.
    c. Accepts incoming records via MockSocket.
    d. Calls node->put() to store them.

6. Monitoring Module
    a. Collects per-node statistics (PUTs, GETs, record counts).
    b. Prints a summary report after the load job.

7. Verification Module
    a. Confirms each record is stored on its correct owning node.
    b. Prints a verification report (correct vs incorrect).

WorkFlow in Sort:
Config → Load → Distribute (via mock network) → Store → Monitor → Verify

## Compiler Details:
We are using G++ compiler from MSYS2 (https://www.msys2.org/)
Text Editor used : VS Code

## To Compile use below:
Required C++ 20 for json-develop library
If You are Compiling from Distribution_System Folder: g++ src/main.cpp -I include -I ../json-develop/include src/ConfigManager.cpp src/DataLoader.cpp src/DistributionEngine.cpp src/Node.cpp src/Verification.cpp src/MockNetwork.cpp -o Distributed_System
To run the application in Command line:  ./Distributed_System
