#include "../include/HistoricalStorage.hpp"
#include <sqlite3.h>
#include <stdexcept>
#include <filesystem>  

// Constructor for HistoricalStorage, initializes the database at the given path
HistoricalStorage::HistoricalStorage(const std::string& dbPath) : dbPath_(dbPath) {
    // Create a filesystem path object from the database path
    std::filesystem::path path(dbPath_);
    // Ensure the parent directory for the database exists (creates it if not)
    std::filesystem::create_directories(path.parent_path());

    sqlite3* db; // Pointer for the SQLite database connection
    // Open the SQLite database at the specified path
    if (sqlite3_open(dbPath_.c_str(), &db)) {
        // If opening fails, throw an exception with an error message
        throw std::runtime_error("Failed to open database: " + dbPath_);
    }

    // SQL statement to create the risk_data table if it doesn't exist
    const char* createTable = R"(
        CREATE TABLE IF NOT EXISTS risk_data (
            coin TEXT,
            risk REAL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    char* errMsg = nullptr; // Pointer for error messages from SQLite
    // Execute the SQL statement to create the table
    if (sqlite3_exec(db, createTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        // If execution fails, save the error message
        std::string error = errMsg;
        // Free the error message memory
        sqlite3_free(errMsg);
        // Close the database connection
        sqlite3_close(db);
        // Throw an exception with the error message
        throw std::runtime_error("DB error: " + error);
    }

    // Close the database connection
    sqlite3_close(db);
}

// Inserts a new risk record into the risk_data table
void HistoricalStorage::insertRiskRecord(const std::string& coin, double riskScore) {
    sqlite3* db; // Pointer for the SQLite database connection
    // Open the SQLite database at the stored path
    if (sqlite3_open(dbPath_.c_str(), &db)) {
        // If opening fails, throw an exception
        throw std::runtime_error("Failed to open database for insert.");
    }

    // Build the SQL insert statement with the coin and riskScore values
    std::string sql = "INSERT INTO risk_data (coin, risk) VALUES ('" + coin + "', " + std::to_string(riskScore) + ");";
    char* errMsg = nullptr; // Pointer for error messages from SQLite
    // Execute the SQL insert statement
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        // If execution fails, save the error message
        std::string error = errMsg;
        // Free the error message memory
        sqlite3_free(errMsg);
        // Close the database connection
        sqlite3_close(db);
        // Throw an exception with the error message
        throw std::runtime_error("Insert error: " + error);
    }

    // Close the database connection
    sqlite3_close(db);
}
