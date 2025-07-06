#pragma once
#include <string>
#include <vector>

struct Config {
    std::string coingecko_api_key;
    std::string etherscan_api_key;
    std::string news_api_key;
    std::string thegraph_api_token;
    std::vector<std::string> stablecoins;

    Config();
};
