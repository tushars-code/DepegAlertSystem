#include "AlertManager.hpp"
#include <iostream>

bool AlertManager::shouldAlert(double riskScore) {
    return riskScore > 0.6;
}

void AlertManager::generate(double riskScore, const std::string& coin, double confidence, const std::vector<std::string>& triggers) {
    std::cout << "[ALERT] 🚨 Potential depeg detected!\n";
    std::cout << "Coin: " << coin << "\nRisk Score: " << riskScore << "\nConfidence: " << confidence << "\nTriggers:\n";
    for (const auto& t : triggers) std::cout << " - " << t << "\n";
}
