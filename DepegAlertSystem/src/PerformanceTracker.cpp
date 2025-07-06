#include "../include/PerformanceTracker.hpp"
#include <iostream>

void PerformanceTracker::log(double risk) {
    history.push_back(risk);
}

double PerformanceTracker::averageRisk() const {
    if (history.empty()) return 0.0;
    double total = 0;
    for (double r : history) total += r;
    return total / history.size();
}

void PerformanceTracker::logStageTiming(const std::string& stage, const std::chrono::steady_clock::time_point& start) {
    auto end = std::chrono::steady_clock::now();
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "[PERF] " << stage << " took " << durationMs << " ms\n";
}
