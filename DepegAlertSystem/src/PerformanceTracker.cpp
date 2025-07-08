#include "../include/PerformanceTracker.hpp"
#include <iostream>

// Adds a new risk value to the history vector
void PerformanceTracker::log(double risk) {
    history.push_back(risk); // Store the risk value for later analysis
}

// Calculates the average of all logged risk values
double PerformanceTracker::averageRisk() const {
    if (history.empty()) return 0.0; // If no values are logged, return 0.0
    double total = 0;                // Initialize total sum to zero
    for (double r : history)         // Iterate through each risk value in history
        total += r;                  // Add each risk value to the total
    return total / history.size();   // Return the average risk
}

// Logs the time taken for a specific stage of processing
void PerformanceTracker::logStageTiming(const std::string& stage, const std::chrono::steady_clock::time_point& start) {
    auto end = std::chrono::steady_clock::now(); // Get the current time as the end time
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Calculate duration in milliseconds
    std::cout << "[PERF] " << stage << " took " << durationMs << " ms\n"; // Print the stage name and duration
}
