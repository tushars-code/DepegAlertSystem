#include "../include/SentimentAnalyzer.hpp"

// Analyzes the sentiment of news articles based on their titles
double SentimentAnalyzer::analyzeNewsSentiment(const nlohmann::json& newsData) {
    int positive = 0; // Counter for positive sentiment (decremented for negative, incremented for positive/neutral)
    int total = 0;    // Counter for total number of articles processed

    // Iterate over each article in the "articles" array of the JSON input
    for (const auto& article : newsData["articles"]) {
        std::string title = article["title"]; // Extract the title of the article

        // Check if the title contains negative keywords ("crash" or "depeg")
        if (title.find("crash") != std::string::npos || title.find("depeg") != std::string::npos) {
            positive--; // Decrement positive counter for negative sentiment
        }
        else {
            positive++; // Increment positive counter for positive/neutral sentiment
        }
        total++; // Increment the total articles counter
    }

    // Calculate and return the normalized sentiment score:
    // If there are articles, map the score to [0,1] where 1 is all positive, 0 is all negative, 0.5 is neutral.
    // If no articles, return neutral sentiment (0.5).
    return total > 0 ? (positive + total) / (2.0 * total) : 0.5;
}
