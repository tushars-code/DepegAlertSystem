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

/**
 * This function currently only prints a message to the console to simulate
 * a connection. No actual network connection is made.
 */
void WebSocketClient::connect(const std::string& url) {
    std::cout << "[WebSocket Boost] Simulating connection to: " << url << std::endl;
}

/**
 * Registers a callback to handle incoming WebSocket messages.
 *
 * The provided callback will be invoked with the message payload when a message is received.
 *
 * 0callback A function to handle incoming messages.
 */
void WebSocketClient::onMessage(std::function<void(const std::string&)> callback) {
    messageHandler = callback;
}

/**
 *
 * This function prints a message to the console and, if a message handler is set,
 * invokes it with a hardcoded JSON payload representing a price update event.
 */
void WebSocketClient::run() {
    std::cout << "[WebSocket Boost] Simulating price feed..." << std::endl;
    if (messageHandler) {
        messageHandler("{\"event\":\"price_update\",\"data\":{\"usdt\":0.991}}");
    }
}
