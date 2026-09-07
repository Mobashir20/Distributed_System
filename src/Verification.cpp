#include "../include/Verification.h"
#include <iostream>

void Verification::verifyRecords(DistributionEngine& engine, const DataLoader& loader, bool verbose) {
    std::cout << "\n=== Verification Report ===\n";
    int correct = 0, incorrect = 0;

    for (const auto& rec : loader.getRecords()) {
        std::string key = rec.fields[0];
        std::string value;
        for (std::size_t i = 1; i < rec.fields.size(); ++i) {
            value += rec.fields[i] + " ";
        }

        // Ask engine which node owns this key
        Node* owner = engine.getNodeForKey(key);
        std::string stored = owner->get(key);

        //Console Log to show the verified records
        if (verbose) {
            if (stored == value) {
                std::cout << "Record [" << key << "] correctly stored on Node "
                      << owner->getId() << "\n";
            correct++;
            } else {
                std::cout << "Record [" << key << "] INCORRECTLY stored!\n";
            incorrect++;
            }
        }

        if (stored == value)
            correct++;
        else
            incorrect++;
        
    }

    std::cout << "\nVerification Summary: "
              << correct << " correct, "
              << incorrect << " incorrect.\n";
    std::cout << "============================\n";
}
