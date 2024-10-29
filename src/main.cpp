#include "OrderExecutionSystem.h"
#include "WebSocketServer.h"

int main() {
    std::string access_token = "your_api_token"; // Replace with your actual access token
    std::string client_id = "pNVpbU_e"; // Your API client ID
    std::string client_secret = "ycD8dKlCwyy92fJWdL6FrhmzOykfE1spDmh48zipRt8"; // Your API client secret

    OrderExecutionSystem orderSystem(access_token, client_id, client_secret);
    WebSocketServer wsServer;

    // Example usage
    orderSystem.placeOrder("BTC-PERPETUAL", "buy", 1, 30000.0);
    wsServer.start(); // Start the WebSocket server

    return 0;
}
