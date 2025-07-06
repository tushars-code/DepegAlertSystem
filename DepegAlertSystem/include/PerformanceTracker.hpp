#pragma once
#include <vector>
#include <string>
#include <chrono>

class PerformanceTracker {
public:
    void log(double risk);
    double averageRisk() const;

    void logStageTiming(const std::string& stage, const std::chrono::steady_clock::time_point& start);

private:
    std::vector<double> history;
};
