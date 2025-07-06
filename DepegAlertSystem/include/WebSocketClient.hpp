#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

#include <string>
#include <functional>

class WebSocketClient {
public:
    void connect(const std::string& url);
    void onMessage(std::function<void(const std::string&)> callback);
    void run();

private:
    std::function<void(const std::string&)> messageHandler;
};

#endif 
