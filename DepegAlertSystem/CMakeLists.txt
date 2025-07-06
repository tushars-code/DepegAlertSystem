cmake_minimum_required(VERSION 3.15)

project(DepegAlertSystem)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "include/*.hpp"
)

add_executable(DepegAlertSystem ${SOURCES} ${HEADERS})


target_include_directories(DepegAlertSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/websocketpp  
)

set_target_properties(DepegAlertSystem PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS beast system)


target_link_libraries(DepegAlertSystem
    PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
       
        OpenSSL::Crypto
        unofficial::sqlite3::sqlite3
        Boost::beast
        Boost::system
)
