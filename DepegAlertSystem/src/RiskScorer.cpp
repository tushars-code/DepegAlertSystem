#include "../include/RiskScorer.hpp"

/*
    computeRisk:
    - Calculates a composite risk score based on price deviation, flow metrics, and a historical score.
    - Each component is weighted and summed, then capped at 1.0.
*/
double RiskScorer::computeRisk(const std::map<std::string, double>& priceDeviation,
    const std::map<std::string, double>& flowMetrics,
    double historicalScore) {
    // Set weights for each risk component
    double pdWeight = 0.4;   // Weight for price deviation
    double fmWeight = 0.4;   // Weight for flow metrics
    double histWeight = 0.2; // Weight for historical score

    // Sum the absolute values of all price deviations
    double pdSum = 0.0;
    for (const auto& [_, val] : priceDeviation)
        pdSum += std::abs(val);

    // Sum all flow metric values
    double fmSum = 0.0;
    for (const auto& [_, val] : flowMetrics)
        fmSum += val;

    // Calculate the weighted sum of all components
    double weighted = pdWeight * pdSum + fmWeight * fmSum + histWeight * historicalScore;

    // Cap the risk score at 1.0 and return
    return std::min(weighted, 1.0);
}
