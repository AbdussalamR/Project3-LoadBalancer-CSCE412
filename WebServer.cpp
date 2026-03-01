#include "WebServer.h"

/**
 * @brief Initializes the server with a name and sets it to available.
 */
WebServer::WebServer(char server_name) : name(server_name), time_remaining(0) {}

/**
 * @brief Returns whether the server is currently free.
 */
bool WebServer::isAvailable() const {
    if (time_remaining <= 0) {
        return true;
    }
    return false;
}

/**
 * @brief Starts processing a new request.
 */
void WebServer::startRequest(Request r) {
    current_request = r;
    time_remaining = r.time;
}

/**
 * @brief Decrements the remaining processing time by one clock cycle.
 */
void WebServer::decreaseTime() {
    if (time_remaining > 0) {
        time_remaining--;
    }
}