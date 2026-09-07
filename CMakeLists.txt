cmake_minimum_required(VERSION 3.14)
project(Distributed_System CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable multi-threading support
find_package(Threads REQUIRED)

# Include Header Directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../json-develop/include
)

# Collect Source Files
set(SOURCE_FILES
    src/main.cpp
    src/ConfigManager.cpp
    src/DataLoader.cpp
    src/DistributionEngine.cpp
    src/Node.cpp
    src/Verification.cpp
    src/MockNetwork.cpp
    src/HashUtils.cpp
)

# Define Main Executable with a unique target name (e.g., Distributed_System_App)
add_executable(Distributed_System_App ${SOURCE_FILES})

# Link Threading Libraries
target_link_libraries(Distributed_System_App PRIVATE Threads::Threads)

# Keep the output binary file name as "Distributed_System" (or Distributed_System.exe on Windows)
set_target_properties(Distributed_System_App PROPERTIES OUTPUT_NAME "Distributed_System")