#include "../include/PredictionEngine.hpp"
#include <cmath>

/*
    computeRiskScore:
    - Calculates the risk score for a given coin based on its price deviation from 1.0 (assumed peg value).
    - The further the price deviates from 1.0, the higher the risk score.
    - Returns:
        0.9 if deviation > 0.05
        0.6 if deviation > 0.03
        0.3 if deviation > 0.01
        0.1 otherwise
*/
double PredictionEngine::computeRiskScore(const std::string& coin, double price) {
    double deviation = std::abs(price - 1.0);
    if (deviation > 0.05) return 0.9;
    if (deviation > 0.03) return 0.6;
    if (deviation > 0.01) return 0.3;
    return 0.1;
}

/*
    assessDepegRisk:
    - Takes a map of coin names to their prices.
    - For each coin, computes the risk score using computeRiskScore.
    - Returns a map of coin names to their calculated risk scores.
*/
std::map<std::string, double> PredictionEngine::assessDepegRisk(const std::map<std::string, double>& prices) {
    std::map<std::string, double> risks;
    for (const auto& pair : prices) {
        risks[pair.first] = computeRiskScore(pair.first, pair.second);
    }
    return risks;
}
