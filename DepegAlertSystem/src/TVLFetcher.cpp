#include "../include/TVLFetcher.hpp"
#include <cpr/cpr.h>
#include <stdexcept>

nlohmann::json TVLFetcher::fetchTVL(const std::string& query) {
    auto res = cpr::Post(
        cpr::Url{ "https://api.thegraph.com/subgraphs/name/protocol/subgraph" },
        cpr::Body{ query },
        cpr::Header{ {"Content-Type", "application/json"} }
    );

    if (res.status_code != 200) throw std::runtime_error("TVL fetch failed");
    return nlohmann::json::parse(res.text);
}
