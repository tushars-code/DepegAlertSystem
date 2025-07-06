#include "../include/RiskScorer.hpp"

double RiskScorer::computeRisk(const std::map<std::string, double>& priceDeviation,
    const std::map<std::string, double>& flowMetrics,
    double historicalScore) {
    double pdWeight = 0.4;
    double fmWeight = 0.4;
    double histWeight = 0.2;

    double pdSum = 0.0;
    for (const auto& [_, val] : priceDeviation) pdSum += std::abs(val);

    double fmSum = 0.0;
    for (const auto& [_, val] : flowMetrics) fmSum += val;

    double weighted = pdWeight * pdSum + fmWeight * fmSum + histWeight * historicalScore;
    return std::min(weighted, 1.0);
}
