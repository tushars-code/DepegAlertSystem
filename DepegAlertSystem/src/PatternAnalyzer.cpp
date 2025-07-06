#include "../include/PatternAnalyzer.hpp"

double PatternAnalyzer::compareToHistoricalPatterns(const std::map<std::string, double>& priceDeviation,
    const std::map<std::string, double>& flowMetrics) {
    double deviationSum = 0.0;
    for (const auto& pair : priceDeviation) deviationSum += std::abs(pair.second);
    for (const auto& pair : flowMetrics) deviationSum += pair.second;
    return deviationSum / (priceDeviation.size() + flowMetrics.size());
}
