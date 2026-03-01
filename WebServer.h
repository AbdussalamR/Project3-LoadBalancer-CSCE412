#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Simulates a single web server in the load balancing system.
 *
 * A WebServer can process one Request at a time.
 * It tracks the time remaining to complete the request
 * and reports when it becomes available.
 */
class WebServer {
public:

    char name;                 ///< Identifier for the server
    Request current_request;   ///< The request currently being processed
    int time_remaining;        ///< Clock cycles remaining for current request

    /**
     * @brief Constructs a WebServer with a given name.
     * @param server_name A character identifier for the server.
     */
    WebServer(char server_name);

    /**
     * @brief Checks whether the server is available.
     * @return True if no request is being processed.
     */
    bool isAvailable() const;

    /**
     * @brief Assigns a new request to the server.
     * @param r The request to process.
     */
    void startRequest(Request r);

    /**
     * @brief Simulates one clock cycle of processing.
     *
     * Decreases the remaining time if the server is busy.
     */
    void decreaseTime();
};

#endif