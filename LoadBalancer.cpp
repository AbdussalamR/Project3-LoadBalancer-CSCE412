#include "LoadBalancer.h"
#include <iostream>

/**
 * @brief Constructs a LoadBalancer and initializes servers.
 * 
 * Opens log file, sets system time to 0, and creates the
 * specified number of initial web servers.
 */
LoadBalancer::LoadBalancer(int startServers) :systemTime(0) {
    logFile.open("log.txt");
    log("LoadBalancer initialized with " + std::to_string(startServers) + " servers.");
    for (int i = 0; i < startServers; i++) {
        servers.push_back(WebServer('A' + i));
    }
}

/**
 * @brief Destructor.
 * 
 * Ensures log file is properly closed.
 */
LoadBalancer::~LoadBalancer() {
    logFile.close();
}

/**
 * @brief Adds a request to the queue if not blocked.
 * 
 * If the IP address is blocked by the firewall,
 * the request is denied and logged.
 */
void LoadBalancer::addRequest(Request r) {
    if (isBlocked(r.ip_in)) {
        log("Firewall Block: Request from " + r.ip_in + " is denied.");
        return;
    }
    requestQueue.push(r);
}

/**
 * @brief Determines if an IP address should be blocked.
 * 
 * Current implementation blocks any IP starting
 * with the digit '2'.
 * 
 * @param ip Incoming IP address.
 * @return True if IP is blocked.
 */
bool LoadBalancer::isBlocked(std::string ip) {
    return (ip[0] == '2');
}

/**
 * @brief Assigns queued requests to idle servers and advances simulation.
 * 
 * For each server:
 * - If available and queue is not empty → assign request
 * - Decrease processing time
 * 
 * Increments system clock at end of cycle.
 */
void LoadBalancer::req_to_idle_server() {
    for (auto& server : servers) {
        if (server.isAvailable() && !requestQueue.empty()) {
            Request r = requestQueue.front();
            requestQueue.pop();
            server.startRequest(r);
            log("Assigned request from " + r.ip_in + " to server " + server.name);
        }
        server.decreaseTime();
    }
    systemTime++;
}

/**
 * @brief Dynamically adds or removes servers based on queue size.
 * 
 * Scaling Rules:
 * - If queue > 80 × number_of_servers → add server
 * - If queue < 50 × number_of_servers → remove server (if idle)
 */
void LoadBalancer::dynamic_allocation() {
    int qSize = requestQueue.size();
    int sSize = servers.size();

    if (qSize > 80 * sSize) {
        servers.push_back(WebServer('S' + sSize));
        log("SCALING EVENT: Load high (" + std::to_string(qSize) + "). Adding server.");
    }
    else if (qSize < 50 * sSize && sSize > 1) {
        if (servers.back().isAvailable()) {
            log("SCALING EVENT: Load low (" + std::to_string(qSize) + "). Removing server " + servers.back().name);
            servers.pop_back();
        }   
    }
}

/**
 * @brief Writes a timestamped message to the log file.
 * 
 * @param message Event message to log.
 */
void LoadBalancer::log(std::string message) {
    logFile << "Time " << systemTime << ": " << message << std::endl;
}