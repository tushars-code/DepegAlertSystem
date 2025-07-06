#pragma once
#include <map>
#include <string>

class RiskScorer {
public:
    double computeRisk(const std::map<std::string, double>& priceDeviation,
        const std::map<std::string, double>& flowMetrics,
        double historicalScore);
};
