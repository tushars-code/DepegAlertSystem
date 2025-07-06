#include "../include/PerformanceTracker.hpp"

void PerformanceTracker::log(double risk) {
    history.push_back(risk);
}

double PerformanceTracker::averageRisk() const {
    if (history.empty()) return 0.0;
    double total = 0;
    for (double r : history) total += r;
    return total / history.size();
}
