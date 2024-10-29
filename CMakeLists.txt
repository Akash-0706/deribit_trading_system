cmake_minimum_required(VERSION 3.10)
project(DeribitTradingSystem)

set(CMAKE_CXX_STANDARD 17)

# Custom paths for libraries
set(CURL_INCLUDE_DIR "/opt/homebrew/opt/curl/include")
set(CURL_LIBRARY "/opt/homebrew/opt/curl/lib/libcurl.dylib")
set(JSON_INCLUDE_DIR "/opt/homebrew/Cellar/nlohmann-json/3.11.3/include")
set(WEBSOCKETPP_INCLUDE_DIR "/opt/homebrew/Cellar/websocketpp/0.8.2/include")
set(BOOST_INCLUDE_DIR "/opt/homebrew/include/")

# Include directories for the libraries
include_directories(${CURL_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${WEBSOCKETPP_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})

# Add the executable target
add_executable(DeribitTradingSystem 
    src/main.cpp 
    src/OrderExecutionSystem.cpp 
    src/HttpClient.cpp 
    src/WebSocketServer.cpp
)

# Link libraries
target_link_libraries(DeribitTradingSystem ${CURL_LIBRARY} pthread)
