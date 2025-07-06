#include "../include/DataIngestor.hpp"
#include "../include/Config.hpp"
#include <cpr/cpr.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <mutex>

static std::mutex cache_mutex;
static std::string cached_eth_address;
static nlohmann::json cached_eth_result;

DataIngestor::DataIngestor() {
    Config cfg;
    coingecko_key = cfg.coingecko_api_key;
    etherscan_key = cfg.etherscan_api_key;
    newsapi_key = cfg.news_api_key;
    thegraph_token = cfg.thegraph_api_token;
}

nlohmann::json DataIngestor::fetchCoinGeckoPrices(const std::vector<std::string>& coins) {
    std::string ids;
    for (const auto& coin : coins) {
        ids += coin + ",";
    }
    if (!ids.empty()) ids.pop_back();

    auto r = cpr::Get(cpr::Url{ "https://api.coingecko.com/api/v3/simple/price" },
        cpr::Parameters{ {"ids", ids}, {"vs_currencies", "usd"} },
        cpr::Header{ {"x-cg-api-key", coingecko_key} });

    if (r.status_code != 200) throw std::runtime_error("CoinGecko error");
    return nlohmann::json::parse(r.text);
}

nlohmann::json DataIngestor::fetchEtherscanTx(const std::string& address) {
    std::lock_guard<std::mutex> lock(cache_mutex);
    if (address == cached_eth_address && !cached_eth_result.empty()) {
        std::cout << "[CACHE] Returning cached Etherscan result\n";
        return cached_eth_result;
    }

    auto r = cpr::Get(cpr::Url{ "https://api.etherscan.io/api" },
        cpr::Parameters{ {"module", "account"},
                         {"action", "tokentx"},
                         {"contractaddress", address},
                         {"startblock", "0"},
                         {"endblock", "99999999"},
                         {"sort", "desc"},
                         {"apikey", etherscan_key} });

    if (r.status_code != 200) throw std::runtime_error("Etherscan error");

    cached_eth_address = address;
    cached_eth_result = nlohmann::json::parse(r.text);
    return cached_eth_result;
}

nlohmann::json DataIngestor::fetchNewsSentiment(const std::string& coin) {
    auto r = cpr::Get(cpr::Url{ "https://newsapi.org/v2/everything" },
        cpr::Parameters{ {"q", coin}, {"language", "en"}, {"sortBy", "publishedAt"}, {"apiKey", newsapi_key} });

    if (r.status_code != 200) throw std::runtime_error("NewsAPI error");
    return nlohmann::json::parse(r.text);
}

nlohmann::json DataIngestor::fetchTheGraphTVL(const std::string& query) {
    auto r = cpr::Post(cpr::Url{ "https://gateway.thegraph.com/api/" + thegraph_token + "/subgraphs/id/server_c2df603ddcd3181d5237e66fb2b500a6" },
        cpr::Body{ query },
        cpr::Header{ {"Content-Type", "application/json"} });

    if (r.status_code != 200) throw std::runtime_error("TheGraph error");
    return nlohmann::json::parse(r.text);
}
