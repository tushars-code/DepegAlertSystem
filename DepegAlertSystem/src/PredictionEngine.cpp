#include "../include/PredictionEngine.hpp"
#include <cmath>

double PredictionEngine::computeRiskScore(const std::string& coin, double price) {
    double deviation = std::abs(price - 1.0);
    if (deviation > 0.05) return 0.9;
    if (deviation > 0.03) return 0.6;
    if (deviation > 0.01) return 0.3;
    return 0.1;
}

std::map<std::string, double> PredictionEngine::assessDepegRisk(const std::map<std::string, double>& prices) {
    std::map<std::string, double> risks;
    for (const auto& pair : prices) {
        risks[pair.first] = computeRiskScore(pair.first, pair.second);
    }
    return risks;
}
