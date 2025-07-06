#pragma once
#include <string>
#include <vector>

class AlertManager {
public:
    bool shouldAlert(double riskScore);
    void generate(double riskScore, const std::string& coin, double confidence, const std::vector<std::string>& triggers);
};
