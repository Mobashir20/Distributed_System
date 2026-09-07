#pragma once
#include <unordered_map>
#include <string>
#include <mutex>

class Node {
public:
    explicit Node(int id) : node_id(id) {}

    void put(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mtx);
        store[key] = value;
        ++put_count;
    }

    std::string get(const std::string& key) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = store.find(key);
        ++get_count;
        return it != store.end() ? it->second : "NOT_FOUND";
    }

    int getId() const { return node_id; }
    std::size_t getRecordCount() const { return store.size(); }
    std::size_t getPutCount() const { return put_count; }
    std::size_t getGetCount() const { return get_count; }

    // Save node data to disk/file
    void persist(const std::string& folder);

private:
    int node_id;
    std::unordered_map<std::string, std::string> store;
    mutable std::mutex mtx;
    std::size_t put_count = 0;
    std::size_t get_count = 0;
};
