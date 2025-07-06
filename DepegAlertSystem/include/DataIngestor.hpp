#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

class DataIngestor {
public:
    DataIngestor();
    nlohmann::json fetchCoinGeckoPrices(const std::vector<std::string>& coins);
    nlohmann::json fetchEtherscanTx(const std::string& address);
    nlohmann::json fetchNewsSentiment(const std::string& coin);
    nlohmann::json fetchTheGraphTVL(const std::string& query);
private:
    std::string coingecko_key;
    std::string etherscan_key;
    std::string newsapi_key;
    std::string thegraph_token;
};
