#include "../include/PatternAnalyzer.hpp"

// Compares current metrics to historical patterns by calculating an average deviation score
double PatternAnalyzer::compareToHistoricalPatterns(const std::map<std::string, double>& priceDeviation,
    const std::map<std::string, double>& flowMetrics) {
    double deviationSum = 0.0; // Initialize sum of deviations to zero

    // Add the absolute value of each price deviation to the sum
    for (const auto& pair : priceDeviation)
        deviationSum += std::abs(pair.second);

    // Add each flow metric value to the sum (assumed already positive or meaningful as-is)
    for (const auto& pair : flowMetrics)
        deviationSum += pair.second;

    // Calculate the average deviation by dividing the sum by the total number of entries
    // (priceDeviation count + flowMetrics count)
    return deviationSum / (priceDeviation.size() + flowMetrics.size());
}
