#include "AlertManager.hpp"
#include <iostream>

// Determines if an alert should be triggered based on the risk score
bool AlertManager::shouldAlert(double riskScore) {
    // Return true if the risk score is greater than 0.6, otherwise false
    return riskScore > 0.6;
}

// Generates and prints an alert message with details
void AlertManager::generate(double riskScore, const std::string& coin, double confidence, const std::vector<std::string>& triggers) {
    // Print the alert header
    std::cout << "[ALERT] 🚨 Potential depeg detected!\n";
    // Print the coin name
    std::cout << "Coin: " << coin << "\nRisk Score: " << riskScore << "\nConfidence: " << confidence << "\nTriggers:\n";
    // Iterate through each trigger and print it
    for (const auto& t : triggers)
        std::cout << " - " << t << "\n";
}
