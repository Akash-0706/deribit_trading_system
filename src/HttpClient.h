#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <nlohmann/json.hpp>

class HttpClient {
public:
    HttpClient(const std::string& accessToken);
    void setApiKeys(const std::string& clientId, const std::string& clientSecret);
    nlohmann::json post(const std::string& url, const nlohmann::json& payload);
    nlohmann::json get(const std::string& url);

private:
    std::string access_token;
    std::string client_id;
    std::string client_secret;
};

#endif
