#include "HttpClient.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

HttpClient::HttpClient(const std::string& token) : access_token(token) {}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

nlohmann::json HttpClient::post(const std::string& url, const nlohmann::json& payload) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.dump().c_str());

        // Set up headers with CORS allowance
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        headers = curl_slist_append(headers, "Access-Control-Allow-Origin: *");  // Enable CORS
        headers = curl_slist_append(headers, "Access-Control-Allow-Methods: GET, POST, OPTIONS");
        headers = curl_slist_append(headers, "Access-Control-Allow-Headers: Content-Type, Authorization");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        curl_slist_free_all(headers);  // Free headers
        curl_easy_cleanup(curl);
    }

    return nlohmann::json::parse(readBuffer);
}

nlohmann::json HttpClient::get(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) return {};

    std::string response_string;

    // Set up headers with CORS allowance
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
    headers = curl_slist_append(headers, "Access-Control-Allow-Origin: *");  // Enable CORS
    headers = curl_slist_append(headers, "Access-Control-Allow-Methods: GET, POST, OPTIONS");
    headers = curl_slist_append(headers, "Access-Control-Allow-Headers: Content-Type, Authorization");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);  // Free headers
    curl_easy_cleanup(curl);

    return nlohmann::json::parse(response_string);
}
