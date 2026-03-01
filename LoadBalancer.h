#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include <vector>
#include <queue>
#include <fstream>

/**
 * @class LoadBalancer
 * @brief Manages web servers and distributes incoming requests.
 *
 * The LoadBalancer:
 * - Maintains a queue of requests
 * - Assigns requests to idle servers
 * - Dynamically adds/removes servers based on load
 * - Blocks requests from restricted IP ranges
 * - Logs system events
 */
class LoadBalancer {
public:
    int systemTime;                         ///< Tracks the current time in clock cycles
    std::queue<Request> requestQueue;       ///< Queue of incoming requests waiting to be processed
    std::vector<WebServer> servers;         ///< List of active web servers
    std::ofstream logFile;                  ///< File stream for logging events

    int numStart;       /**< Track initial queue size */
    int blockedCount;   /**< Track Firewall rejections (Req 15) */
    int tasksDone;      /**< Track completed tasks */

    /**
     * @brief Constructs a LoadBalancer with an initial number of servers.
     * @param startServers Number of servers to initialize.
     */
    LoadBalancer(int startServers);

    /**
     * @brief Destructor closes log file.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a request to the queue if not blocked.
     * @param r Request to be added.
     */
    void addRequest(Request r);

    /**
     * @brief Assigns requests to idle servers and advances time.
     */
    void req_to_idle_server();

    /**
     * @brief Dynamically adds or removes servers based on queue size.
     */
    void dynamic_allocation();

    /**
     * @brief Determines if an IP address should be blocked.
     * @param ip IP address string.
     * @return True if blocked.
     */
    bool isBlocked(std::string ip);

    /**
     * @brief Logs a message with timestamp.
     * @param message Message to write to log file.
     */
    void log(std::string message);

};

#endif