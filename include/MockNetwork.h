#include <string>
#include <iostream>

using namespace std;

// Simple mock of socket-like behavior
class MockSocket {
public:
    explicit MockSocket(int id) : socket_id(id) {}

    bool connect(int target_id) {
        cout << "[MockSocket] Node " << socket_id
                  << " connecting to Node " << target_id << "\n";
        return true; // always succeeds in mock
    }

    bool send(const std::string& data) {
        cout << "[MockSocket] Node " << socket_id
              << " sending data: " << data << "\n";
        last_sent = data;
        return true;
    }

    std::string recv() {
        cout << "[MockSocket] Node " << socket_id
              << " receiving data: " << last_sent << "\n";
        return last_sent;
    }

private:
    int socket_id;
    string last_sent;
};
