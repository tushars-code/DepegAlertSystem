# 🛡️ DepegAlertSystem

A high-performance C++ backend system to predict and alert on **stablecoin depeg events** using real-time price feeds, on-chain flow analytics, historical pattern detection, and risk modeling.

## Objective

The system aims to:
- Monitor stablecoin stability in **real-time**
- Identify risk factors from **price deviation, wallet flows, TVL drops, sentiment analysis**
- Match current behavior to **historical depeg patterns**
- Generate **alerts** with risk scores, confidence levels, and triggering factors

---

##  Architecture Overview

                       ┌────────────────────┐
                       │  Config + Logger   │
                       └────────┬───────────┘
                                │
                    ┌───────────▼──────────┐
                    │   DataIngestor       │
                    │ (CoinGecko, Etherscan)│
                    └───────────┬──────────┘
                                │
        ┌────────────┬──────────▼─────────────┬─────────────┐
        │            │                        │             │
 ┌──────▼─────┐┌─────▼───────┐        ┌───────▼──────┐┌─────▼──────┐
 │ Sentiment  ││ Pattern     │        │ RiskScorer   ││ TVLFetcher │
 │ Analyzer   ││ Analyzer    │        │ (Multi-factor)││ (optional)│
 └────┬───────┘└──────┬──────┘        └──────────────┘└────────────┘
      │               │
      └────┬──────────┴───────────────┐
           ▼                          ▼
   ┌──────────────┐         ┌────────────────────┐
   │ AlertManager │         │ HistoricalStorage   │
   └──────┬───────┘         └──────────┬──────────┘
          │                            │
          ▼                            ▼
  ┌──────────────┐           ┌────────────────────┐
  │ Risk Alerts  │           │ SQLite DB (risk.db)│
  └──────────────┘           └────────────────────┘


##  Features
- Real-time price fetch via [CoinGecko API]  
- On-chain flow analysis via [Etherscan API]  
- Pattern matching using past depeg behaviors  
- Sentiment analysis from mock news feed  
- SQLite storage for historical risk scoring  
- Configurable alert thresholds  
- Modular and multithreaded architecture  
- Logging and performance tracking  

## Dependencies
- Install with [`vcpkg`](https://github.com/microsoft/vcpkg):
- For pkges(vcpkg install cpr nlohmann-json sqlite3 boost)

## Toolchain 
 your CMakeLists.txt uses the vcpkg toolchain:set(CMAKE_TOOLCHAIN_FILE "C:/Users/<your-user>/vcpkg/scripts/buildsystems/vcpkg.cmake")


## Commands for building
git clone https://github.com/your-username/DepegAlertSystem.git
cd DepegAlertSystem
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/<your-user>/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .

## Sample Output
![image](https://github.com/user-attachments/assets/05636008-6045-44a1-bbc9-b7e49cd72712)

