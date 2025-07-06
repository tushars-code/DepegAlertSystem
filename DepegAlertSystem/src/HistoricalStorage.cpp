#include "../include/HistoricalStorage.hpp"
#include <sqlite3.h>
#include <stdexcept>
#include <filesystem>  

HistoricalStorage::HistoricalStorage(const std::string& dbPath) : dbPath_(dbPath) {
    
    std::filesystem::path path(dbPath_);
    std::filesystem::create_directories(path.parent_path());

    sqlite3* db;
    if (sqlite3_open(dbPath_.c_str(), &db)) {
        throw std::runtime_error("Failed to open database: " + dbPath_);
    }

    const char* createTable = R"(
        CREATE TABLE IF NOT EXISTS risk_data (
            coin TEXT,
            risk REAL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        throw std::runtime_error("DB error: " + error);
    }

    sqlite3_close(db);
}

void HistoricalStorage::insertRiskRecord(const std::string& coin, double riskScore) {
    sqlite3* db;
    if (sqlite3_open(dbPath_.c_str(), &db)) {
        throw std::runtime_error("Failed to open database for insert.");
    }

    std::string sql = "INSERT INTO risk_data (coin, risk) VALUES ('" + coin + "', " + std::to_string(riskScore) + ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        throw std::runtime_error("Insert error: " + error);
    }

    sqlite3_close(db);
}
