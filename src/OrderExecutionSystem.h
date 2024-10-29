#ifndef ORDEREXECUTIONSYSTEM_H
#define ORDEREXECUTIONSYSTEM_H

#include <string>
#include <nlohmann/json.hpp>
#include "HttpClient.h"

class OrderExecutionSystem {
public:
    OrderExecutionSystem(const std::string& token, const std::string& clientId, const std::string& clientSecret);
    bool authenticate();
    bool placeOrder(const std::string& instrument, const std::string& type, double amount, double price);
    bool cancelOrder(const std::string& order_id);
    bool modifyOrder(const std::string& order_id, double amount, double price);
    nlohmann::json getOrderBook(const std::string& instrument);
    nlohmann::json getPosition();

private:
    std::string access_token;
    HttpClient httpClient;
};

#endif
