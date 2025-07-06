#include "../include/SentimentAnalyzer.hpp"

double SentimentAnalyzer::analyzeNewsSentiment(const nlohmann::json& newsData) {
    int positive = 0;
    int total = 0;

    for (const auto& article : newsData["articles"]) {
        std::string title = article["title"];
        if (title.find("crash") != std::string::npos || title.find("depeg") != std::string::npos) {
            positive--;
        }
        else {
            positive++;
        }
        total++;
    }

    return total > 0 ? (positive + total) / (2.0 * total) : 0.5;
}
