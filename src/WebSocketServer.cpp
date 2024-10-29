#include "WebSocketServer.h"
#include <iostream>
#include <functional>

WebSocketServer::WebSocketServer() {
    ws_server.init_asio();
    ws_server.set_message_handler(std::bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
}

void WebSocketServer::start() {
    ws_server.listen(9002);
    ws_server.start_accept();
    ws_server.run();
}

void WebSocketServer::on_message(connection_hdl hdl, server::message_ptr msg) {
    std::string payload = msg->get_payload();
    std::cout << "Received message: " << payload << std::endl;

    // Example: Subscribe to order book updates
    if (payload.find("subscribe") != std::string::npos) {
        std::string symbol = payload.substr(payload.find(" ") + 1);
        subscribeToOrderBook(symbol, hdl);
    }
}

void WebSocketServer::subscribeToOrderBook(const std::string& symbol, connection_hdl hdl) {
    // Implement subscription logic to send updates
    // This is a placeholder; implement actual logic to fetch order book updates
    std::cout << "Subscribed to order book for symbol: " << symbol << std::endl;
}
