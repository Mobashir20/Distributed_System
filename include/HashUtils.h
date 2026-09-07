#pragma once
#include <string>
#include <cstddef>  // for size_t

// Utility namespace for hashing functions
namespace HashUtils {
    // FNV-1a hash implementation for strings
    size_t fnv1aHash(const std::string& key);
}
