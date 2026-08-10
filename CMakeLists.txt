cmake_minimum_required(VERSION 3.10)

project(Distributed_System LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
#include_directories(
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/json-develop/include
)

# Add executable from src/ folder
add_executable(main
    src/main.cpp
    src/ConfigManager.cpp
    src/DataLoader.cpp
    src/DistributionEngine.cpp
    src/Node.cpp
    src/Verification.cpp
    src/MockNetwork.cpp
)
