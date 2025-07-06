#pragma once
#include <string>

class HistoricalStorage {
public:
    HistoricalStorage(const std::string& dbPath);
    void insertRiskRecord(const std::string& coin, double riskScore);
private:
    std::string dbPath_;
};
