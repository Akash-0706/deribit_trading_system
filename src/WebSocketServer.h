#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::connection_hdl;
typedef websocketpp::server<websocketpp::config::asio> server;

class WebSocketServer {
public:
    WebSocketServer();
    void start();
    void on_message(connection_hdl hdl, server::message_ptr msg);
    void subscribeToOrderBook(const std::string& symbol, connection_hdl hdl); // Declaration for subscription

private:
    server ws_server;
};

#endif
