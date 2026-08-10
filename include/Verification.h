#include "DistributionEngine.h"
#include "DataLoader.h"
#include <iostream>

class Verification {
public:
    static void verifyRecords(DistributionEngine& engine, const DataLoader& loader);
};
