#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "../include/Config.hpp"
#include "../include/DataIngestor.hpp"
#include "../include/SentimentAnalyzer.hpp"
#include "../include/PatternAnalyzer.hpp"
#include "../include/RiskScorer.hpp"
#include "../include/AlertManager.hpp"
#include "../include/PerformanceTracker.hpp"
#include "../include/HistoricalStorage.hpp"
#include "../include/Logger.hpp"

int main() {
    Logger::log("System started");

    Config cfg;
    DataIngestor ingestor;
    PatternAnalyzer pattern;
    RiskScorer scorer;
    AlertManager alert;
    PerformanceTracker tracker;
    SentimentAnalyzer sentiment;
    HistoricalStorage db("data/risk.db");

    std::vector<std::thread> workers;

    auto prices = ingestor.fetchCoinGeckoPrices(cfg.stablecoins);
    auto txs = ingestor.fetchEtherscanTx("0xdAC17F958D2ee523a2206206994597C13D831ec7");
    auto news = ingestor.fetchNewsSentiment("USDT");

    std::map<std::string, double> priceDeviation;
    for (const auto& [coin, obj] : prices.items()) {
        priceDeviation[coin] = obj["usd"].get<double>() - 1.0;
    }

    std::map<std::string, double> flowMetrics = {
        {"sentiment_score", sentiment.analyzeNewsSentiment(news)},
        {"large_outflow", 0.6},
        {"wallet_concentration", 0.75},
        {"tvl_drop", 0.22}
    };

    double histScore = pattern.compareToHistoricalPatterns(priceDeviation, flowMetrics);
    double risk = scorer.computeRisk(priceDeviation, flowMetrics, histScore);

    tracker.log(risk);
    db.insertRiskRecord("usdt", risk);

    Logger::log("Risk score: " + std::to_string(risk));

    if (alert.shouldAlert(risk)) {
        alert.generate(risk, "USDT", 0.8, { "TVL drop", "Sentiment risk" });
    }

    Logger::log("System complete");
    return 0;
}
