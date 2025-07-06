#include "../include/WebSocketClient.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>

#include <iostream>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void WebSocketClient::connect(const std::string& url) {
    std::cout << "[WebSocket Boost] Simulating connection to: " << url << std::endl;
}

void WebSocketClient::onMessage(std::function<void(const std::string&)> callback) {
    messageHandler = callback;
}

void WebSocketClient::run() {
    std::cout << "[WebSocket Boost] Simulating price feed..." << std::endl;
    if (messageHandler) {
        messageHandler("{\"event\":\"price_update\",\"data\":{\"usdt\":0.991}}");
    }
}
