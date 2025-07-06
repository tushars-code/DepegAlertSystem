#pragma once
#include <string>
#include <nlohmann/json.hpp>

class TVLFetcher {
public:
    nlohmann::json fetchTVL(const std::string& defiQuery);
};
