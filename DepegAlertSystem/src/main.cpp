/**
 * @brief DepegAlertSystem - Entry point for the high-performance stablecoin depeg risk analysis system.
 * This main function performs the following key actions:

 * 1. Initializes core components: configuration loader, data ingestors, analyzers, scorers, trackers, and storage.
 * 2. Ingests real-time data asynchronously:
 *     - Stablecoin prices from CoinGecko
 *     - On-chain transaction data from Etherscan
 *     - News sentiment data
 
 * 3. Measures and logs latency for each stage using `PerformanceTracker`.
 * 4. Processes and normalizes input data:
 *     - Calculates price deviation from peg
 *     - Constructs flow metrics using sentiment and dummy values for simulation
 * 5. Performs risk analysis:
 *     - Historical pattern matching
 *     - Risk score computation
 *     - Persistence of risk data in SQLite
 * 6. Generates alerts if risk crosses threshold, with trigger factors.
 

 * Performance Features:
 * - Uses `std::async` to parallelize I/O-heavy operations (price/news/on-chain fetch).
 * - Benchmarks each operation using `std::chrono`.
 *
 * Output:
 * - Console logs for timing, risk scores, and alerts
 * - SQLite entry of risk scores
 *
 */


#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <future>  // For async calls
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

    // async tasks
    auto t1 = std::chrono::steady_clock::now();
    auto pricesFuture = std::async(std::launch::async, [&]() {
        return ingestor.fetchCoinGeckoPrices(cfg.stablecoins);
        });

    auto txFuture = std::async(std::launch::async, [&]() {
        return ingestor.fetchEtherscanTx("0xdAC17F958D2ee523a2206206994597C13D831ec7");
        });

    auto newsFuture = std::async(std::launch::async, [&]() {
        return ingestor.fetchNewsSentiment("USDT");
        });

    auto prices = pricesFuture.get();
    tracker.logStageTiming("Price Ingestion", t1);

    auto t2 = std::chrono::steady_clock::now();
    auto txs = txFuture.get();
    tracker.logStageTiming("On-Chain Tx Fetch", t2);

    auto t3 = std::chrono::steady_clock::now();
    auto news = newsFuture.get();
    tracker.logStageTiming("Sentiment Fetch", t3);

    
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

    auto t4 = std::chrono::steady_clock::now();
    double histScore = pattern.compareToHistoricalPatterns(priceDeviation, flowMetrics);
    tracker.logStageTiming("Pattern Matching", t4);

    auto t5 = std::chrono::steady_clock::now();
    double risk = scorer.computeRisk(priceDeviation, flowMetrics, histScore);
    tracker.logStageTiming("Risk Calculation", t5);

    tracker.log(risk);
    db.insertRiskRecord("usdt", risk);

    Logger::log("Risk score: " + std::to_string(risk));

    auto t6 = std::chrono::steady_clock::now();
    if (alert.shouldAlert(risk)) {
        alert.generate(risk, "USDT", 0.8, { "TVL drop", "Sentiment risk" });
    }
    tracker.logStageTiming("Alert Trigger", t6);

    Logger::log("System complete");
    return 0;
}
