#pragma once
#include <nlohmann/json.hpp>

class SentimentAnalyzer {
public:
    double analyzeNewsSentiment(const nlohmann::json& newsData);
};
