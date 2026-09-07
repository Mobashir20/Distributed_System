#pragma once
#include <string>
#include <iostream>

// Simple mock of socket-like behavior
class MockSocket {
public:
    explicit MockSocket(int id, bool verbose) : socket_id(id), verbose(verbose) {}

    bool connect(int target_id) {
        if (verbose) {
            std::cout << "[MockSocket] Node " << socket_id
                      << " connecting to Node " << target_id << "\n";
        }
        return true; // always succeeds in mock
    }

    bool send(const std::string& data) {
        if (verbose) {
            std::cout << "[MockSocket] Node " << socket_id
                      << " sending data: " << data << "\n";
        }
        last_sent = data;
        return true;
    }

    std::string recv() {
        if (verbose) {
            std::cout << "[MockSocket] Node " << socket_id
                      << " receiving data: " << last_sent << "\n";
        }
        return last_sent;
    }

private:
    int socket_id;
    bool verbose;
    std::string last_sent;
};
