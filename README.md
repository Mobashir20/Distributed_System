# Distributed_System
You are tasked with implementing a distributed key-value storage and loading system. Each record must be uniquely owned and stored on a single partition or node without replication. The objective is to achieve an even distribution of data across all available (mock) nodes in the cluster.

## Workflow
The loading process consists of the following steps:
  1. Schema Setup: Use config file to specify the schema, consider data types: string, int32.
  2. Data Preparation: Prepare a data file on some or all mock nodes in the cluster, at least 100MB for each file, and may have duplication.
  3. Cluster Start: Start server processes on all mock nodes in the cluster.
  4. Local Reading: Every node reads a local data file existing on some or all cluster nodes.
  5. Record Transfer: Nodes store local records or transfer them to the specific node that owns that record based on the distribution logic.
  6. Statistics: Once the load job finishes, the system must print statistics, including the total number of records loaded per node.
  7. Verification: Provide output confirming successful loading and evidence that records are stored on their corresponding owned nodes.


## Requirements
  1. Implement this in C++.
  2. The cluster can be deployed with (mock, not actual) 1 to 5 nodes depending on configuration.
  3. Schema:
    The schema can contain data types: string, int32, also depending on configuration.
  4. Coding:
    For network I/O: mock functions for POSIX/Berkeley sockets, eg: connect(), send(), recv().
    The system should be optimized for distributed memory usage and efficient network transfers between mock nodes.
    Please write the code as cleanly as possible with good structure and re-usability. 

