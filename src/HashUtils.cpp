#include "HashUtils.h"

namespace HashUtils {
    size_t fnv1aHash(const std::string& key) {
        const size_t fnv_offset_basis = 1469598103934665603ULL;
        const size_t fnv_prime = 1099511628211ULL;
        size_t hash = fnv_offset_basis;
        for (unsigned char c : key) {
            hash ^= c;
            hash *= fnv_prime;
        }
        return hash;
    }
}
