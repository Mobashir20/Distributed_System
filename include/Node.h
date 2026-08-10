#include <unordered_map>
#include <string>
#include <mutex>

using namespace std;

class Node {
public:
    explicit Node(int id) : node_id(id) {}

    void put(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mtx);
        store[key] = value;
    }

    std::string get(const std::string& key) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = store.find(key);
        return it != store.end() ? it->second : "NOT_FOUND";
    }

    int getId() const { return node_id; }
    size_t getRecordCount() const { return store.size(); }
    size_t getPutCount() const { return put_count; }
    size_t getGetCount() const { return get_count; }

    //save node data to disk/file
    void persist(const string &folder);

private:
    int node_id;
    std::unordered_map<std::string, std::string> store;
    mutable std::mutex mtx;
    size_t put_count = 0;
    size_t get_count = 0;
};
