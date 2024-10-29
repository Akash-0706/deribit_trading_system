#include "OrderExecutionSystem.h"

OrderExecutionSystem::OrderExecutionSystem(const std::string& token, const std::string& clientId, const std::string& clientSecret) 
    : access_token(token), httpClient(token) {
    httpClient.setApiKeys(clientId, clientSecret);
}

bool OrderExecutionSystem::placeOrder(const std::string& instrument, const std::string& type, double amount, double price) {
    nlohmann::json order_payload = {
        {"instrument_name", instrument},
        {"amount", amount},
        {"price", price},
        {"type", type}
    };

    nlohmann::json response = httpClient.post("https://test.deribit.com/api/v2/private/" + type, order_payload);
    return response.contains("result");
}

bool OrderExecutionSystem::cancelOrder(const std::string& order_id) {
    nlohmann::json payload = {
        {"order_id", order_id}
    };

    nlohmann::json response = httpClient.post("https://test.deribit.com/api/v2/private/cancel", payload);
    return response.contains("result");
}

bool OrderExecutionSystem::modifyOrder(const std::string& order_id, double amount, double price) {
    nlohmann::json payload = {
        {"order_id", order_id},
        {"amount", amount},
        {"price", price}
    };

    nlohmann::json response = httpClient.post("https://test.deribit.com/api/v2/private/edit", payload);
    return response.contains("result");
}

nlohmann::json OrderExecutionSystem::getOrderBook(const std::string& instrument) {
    nlohmann::json response = httpClient.get("https://test.deribit.com/api/v2/public/get_order_book?instrument_name=" + instrument);
    return response.contains("result") ? response["result"] : nlohmann::json({});
}

nlohmann::json OrderExecutionSystem::getPosition() {
    nlohmann::json response = httpClient.get("https://test.deribit.com/api/v2/private/get_positions");
    return response.contains("result") ? response["result"] : nlohmann::json({});
}
