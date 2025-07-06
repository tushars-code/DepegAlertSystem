#pragma once
#include <map>
#include <string>

class PatternAnalyzer {
public:
    double compareToHistoricalPatterns(const std::map<std::string, double>& priceDeviation,
        const std::map<std::string, double>& flowMetrics);
};
