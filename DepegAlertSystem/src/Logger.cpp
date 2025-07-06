#include "../include/Logger.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

void Logger::log(const std::string& message) {
    std::ofstream logfile("logs/system.log", std::ios::app);
    std::time_t now = std::time(nullptr);
    logfile << std::ctime(&now) << ": " << message << "\n";
    logfile.close();
    std::cout << "[LOG] " << message << "\n";
}
