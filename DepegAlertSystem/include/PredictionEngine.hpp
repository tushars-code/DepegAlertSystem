#pragma once
#include <string>
#include <map>

class PredictionEngine {
public:
    double computeRiskScore(const std::string& coin, double price);
    std::map<std::string, double> assessDepegRisk(const std::map<std::string, double>& prices);
};
