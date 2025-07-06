#pragma once
#include <vector>

class PerformanceTracker {
public:
    void log(double risk);
    double averageRisk() const;
private:
    std::vector<double> history;
};
